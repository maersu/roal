/**     
    This file is part of Roal, a framework for simulations in the field
    of Artificial Intelligence and Aritificial Life.
    See http://roal.sourceforge.net/ for more informations.

    Copyright (c) 2005 Project Roal

    Roal is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Roal is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranerror:ty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Roal; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "DDWalkerMaster.h"

namespace Roal
{

int PhenotypeFitness::usedId = 0; 

bool operator<(const PhenotypeFitness& left, const PhenotypeFitness& right)
{
    return (left.fitness < right.fitness);
}    
    
//------------------------------------------------------------------------------
DDWalkerMaster::DDWalkerMaster(string ipAddress, int port, int poolsize, int parallelPhenotypeCnt)
    : Master(ipAddress, port)
{
    genotype =  new LeggedCreatureGenotype(); 
    genotype->setMinMaxValue("legCount",4,4);
    this->poolsize = poolsize;
    this->parallelPhenotypeCnt = parallelPhenotypeCnt;
    this->genCount = 0;
    generatePhenotypePool();
    
    gnuplotData = new File("/tmp/DDWalkerMaster_lineStat.data");
    gnuplotData->reset();
    gnuplotConfig = new File("/tmp/DDWalkerMaster_lineStat.plot");
    gnuplotConfig->reset();
}


//------------------------------------------------------------------------------
DDWalkerMaster::~DDWalkerMaster()
{
    delete gnuplotData;
    delete gnuplotConfig;
}


//------------------------------------------------------------------------------
void DDWalkerMaster::run()
{
    bool abort = false;
    
    int i = 0;
    
    while(!abort) {     
        usleep(DIST_MASTER_POLLING_SLEEP_US);  
        i++;        
        while (this->connector->hasMessage()) {
            ConnectorMessage* m = this->connector->getNextMessage();
            
            // Register slave
            if ((m->getCommand().compare(DIST_COM_REGISTERSLAVE)) == 0 ) {
                                
                cout << DIST_COM_REGISTERSLAVE << endl;
                this->registerSlave(m->getSessionID());
                            
            // Unregister slave
            } else if ((m->getCommand().compare(DIST_COM_UNREGISTERSLAVE)) == 0 ) {
                
                cout << DIST_COM_UNREGISTERSLAVE <<endl;
                
            // Unregister slave
            } else if ((m->getCommand().compare(POPULATION_EVAL)) == 0 
                                && m->hasValue("PhenotypeNames")) {
                
                cout << POPULATION_EVAL << endl;
                sendPopInitMessage(m->getSessionID(), m->getValue(DIST_AGENT_NAME));
                handleSlaveResult(m); 
                                    
            // Agent needs Population
            } else if ((m->getCommand().compare(NEED_POPULATION)) == 0 
                                                && m->hasValue(DIST_AGENT_NAME)) {
                
                cout << NEED_POPULATION  << endl;                                   
                sendPopInitMessage(m->getSessionID(), m->getValue(DIST_AGENT_NAME));
            // Statistic
            } else if ((m->getCommand().compare(DIST_STAT_FROM_AGENT)) == 0 ) {
                
                cout << DIST_STAT_FROM_AGENT << endl;
                this->handleStatistic(m);
                
            // Unknown message
            } else {
                cerr << "Unknown message from Slave: " << *m << endl;
            }
        }
    }
}

//------------------------------------------------------------------------------
void DDWalkerMaster::sendPopInitMessage(int sid, string agentName)
{
    ConnectorMessage* msg = new ConnectorMessage(sid,INIT_POPULATION); 
    msg->setValue(DIST_AGENT_NAME,agentName);
    string names = "";
    int count = 0;
    
    int hits = 0;
    // try a possible key
    while (hits < parallelPhenotypeCnt ){
        int m = (rand()%phenotypes.size()+1);
        int k = 1;
        for(list<PhenotypeFitness>::iterator it = phenotypes.begin();
        it != phenotypes.end(); it++) 
        {
            if (k==m && it->inUse == false)
            {  
                msg->setValue(toStdStr(it->id),it->phenotype->toString());
                count = it->phenotype->getValuesCount();
                it->inUse = true;
                hits++;
                names = names + toStdStr(it->id)+":";
            }
            k++;
        }
    }  
    
    msg->setValue("PhenotypeValueCount",toStdStr(count));
    msg->setValue("PhenotypeNames",names);
    
    try {
        // create the init message for the slave
        connector->sendMessage(msg);
    } catch (RoalException& e) {
        cerr << "Could not send message: " << e.getMessage() << endl;
    }
    
    
    delete msg;
}

//------------------------------------------------------------------------------
void DDWalkerMaster::handleSlaveResult(ConnectorMessage* msg)
{
    PhenotypeResult results[this->parallelPhenotypeCnt];
    this->genCount++;
    
    int idx=0;
    int loc ;
    int count = 0;
    
    string names = msg->getValue("PhenotypeNames"); 
    string tmp  = "";
       
    loc = names.find( ":", idx);
    while (loc != string::npos)
    {
        tmp = names.substr(idx, loc-idx); 
        PhenotypeResult res;
        res.id = atoi(tmp.c_str());
        res.fitness = atof((msg->getValue(tmp)).c_str());
        
        updatePhenotypeInPool(res.id , res.fitness);
        
        results[count] = res;
        //Next Round
        idx = loc+1;
        loc = names.find( ":", idx );
        count++;
    }
    
    // sort results and pool
    slaveResultsSort(results, 0, this->parallelPhenotypeCnt-1);
    phenotypes.sort();
    phenotypes.reverse();

    // create stats
    updateStatistic();
    
    int nbrOfGoodRates = 0;
    
    // check how many pairs are possible
    if (count/2%1 == 1)
    {
        nbrOfGoodRates = parallelPhenotypeCnt/2-1;
    
    } else 
    {
        nbrOfGoodRates = parallelPhenotypeCnt/2;
    }
    
    // delete the badest
    for (int i = 0; i <  nbrOfGoodRates; i++)
    {
        phenotypes.pop_back();
    }
 
    //crossPhenotypes
    int k = 0;
    while (k < nbrOfGoodRates) 
    {    
        this->crossPhenotypes(results[k].id, results[k+1].id);
        k = k+2;
    }

    //fill up missing Phenos
    generatePhenotypePool();
}

//------------------------------------------------------------------------------
void DDWalkerMaster::generatePhenotypePool()
{
    for (int i=phenotypes.size(); i < poolsize; i++) {
        // Create a random phenotype
        LeggedCreaturePhenotype* phenotype =
                (LeggedCreaturePhenotype*)genotype->getRandomPhenotype();

        PhenotypeFitness tmpFit;
        tmpFit.phenotype = phenotype;
        // Insert new phenotype before the one with next bigger fitness value
        phenotypes.push_back(tmpFit);
    }
}

//------------------------------------------------------------------------------
void DDWalkerMaster::updatePhenotypeInPool(int id, float fitness)
{
    for(list<PhenotypeFitness>::iterator it = phenotypes.begin();
        it != phenotypes.end(); it++) 
    {
        if (it->id == id )
        {  
            it->inUse = false;
            it->fitness = fitness;
        }
    }
}

//------------------------------------------------------------------------------
void DDWalkerMaster::crossPhenotypes(int id1, int id2)
{
    // Get mother and father for reproduction (the two best creatures)
    Phenotype* mother = getPhenotype(id1);
    Phenotype* father = getPhenotype(id2);


    try {
    
        if ((father) && (mother))
        {
            // Prepare two "emtpy phenotype halfes" for the childs
            vector<string> first;
            vector<string> second;
            
            first.push_back("armHeight");
            first.push_back("armLength");
            first.push_back("armWidth");
            first.push_back("force");
        
            second.push_back("bodyHeight");
            second.push_back("bodyLength");
            second.push_back("bodyWidth");
            second.push_back("constValue");
            second.push_back("legCount");
        
            float legCount = mother->getValue("legCount");
            
            for (int i = 1; i <= legCount ; i++) {
                if (i%2 == 0) {
                    first.push_back("axle"+toStdStr(i)+"_Comp1");
                    first.push_back("axle"+toStdStr(i)+"_Comp2");
                    first.push_back("elbow"+toStdStr(i)+"_Comp1");
                    first.push_back("elbow"+toStdStr(i)+"_Comp2");
                    
                } else {
                    second.push_back("axle"+toStdStr(i)+"_Comp1");
                    second.push_back("axle"+toStdStr(i)+"_Comp2");
                    second.push_back("elbow"+toStdStr(i)+"_Comp1");
                    second.push_back("elbow"+toStdStr(i)+"_Comp2");
                }
            }
            
            // Create Childs by crossing mother and father one way and another
            LeggedCreaturePhenotype* child1 = 
                        (LeggedCreaturePhenotype*)mother->crossWith(father, first, second);
            LeggedCreaturePhenotype* child2 = 
                        (LeggedCreaturePhenotype*)mother->crossWith(father, second, first); 
            
            //Safe childs
            PhenotypeFitness c1;
            c1.phenotype = child1;
            phenotypes.push_back(c1);
    
            PhenotypeFitness c2;
            c1.phenotype = child1;
            phenotypes.push_back(c2);
        }
    } catch (RoalException& e) {
        cerr << "Could not cross phenotypes: " << e.getMessage() << endl;
    }
}

//------------------------------------------------------------------------------
Phenotype* DDWalkerMaster::getPhenotype(int id)
{
    for(list<PhenotypeFitness>::iterator it = phenotypes.begin();
        it != phenotypes.end(); it++) 
    {
        if (it->id == id )
        {  
           return it->phenotype;
        }
    }
}

//------------------------------------------------------------------------------
void DDWalkerMaster::deletePhenotype(int id)
{
    for(list<PhenotypeFitness>::iterator it = phenotypes.begin();
        it != phenotypes.end(); it++) 
    {
        if (it->id == id )
        {  
           phenotypes.erase(it,it);
        }
    }
}

//------------------------------------------------------------------------------
void DDWalkerMaster::slaveResultsSort(PhenotypeResult* resultArray,
                                           int left, int right)
{
    if (left >= right) { return; }
    int l = left-1;
    int r = right;
    while (true)
    {
        while ((resultArray[++l].fitness)
                    < ((resultArray[right].fitness)))
        {
            if (l>=r) { break; }
        }
        while ((resultArray[--r].fitness)
                    > ((resultArray[right].fitness)))
        {
            if (l>=r) { break; }
        }
        if (l>=r) { break; }
        
        PhenotypeResult temp = resultArray[l];
        resultArray[l] = resultArray[r];
        resultArray[r] = temp;
    }
    PhenotypeResult temp = resultArray[l];
    resultArray[l] = resultArray[right];
    resultArray[right] = temp;
    
    slaveResultsSort(resultArray, left, l-1);
    slaveResultsSort(resultArray, l+1, right);
}

//------------------------------------------------------------------------------
void DDWalkerMaster::updateStatistic()
{
    
    int resultCount;
    int i = 0;
    //a stat with more than 10 items is not pretty
    if (this->parallelPhenotypeCnt>10)
    {
        resultCount=10;
    } else {
        resultCount=this->parallelPhenotypeCnt;
    }

    string s = "";
    if (this->genCount==1) {
        // Create GnuPlot config file
        string cfg = "set title 'Roal Distributed Dynamic" +s
            + "'\nset xlabel 'Generation'\nset ylabel 'Covered distance [m]'\n" +s
            + "set autoscale\nplot ";
        for (int i=0; i<resultCount; i++) {
            if (i>0) {
                cfg += ", ";
            }
            cfg += "'DDWalkerMaster_lineStat.data' using 1:" + toStdStr(i+2)
                + " with lines title 'Creature " + toStdStr(i+1) + "'";
        }
        cfg += "\npause 30\nreread\n";
        gnuplotConfig->writeln(cfg);
    }    
    
    
    list<PhenotypeFitness>::iterator it = phenotypes.begin();
 
    // Get results of the actual generation for statistics
    string msgStat = toStdStr(this->genCount) + " ";    
    while ((i < resultCount) && (it != phenotypes.end()))
    {
        msgStat += toStdStr(it->fitness)+ " ";
        it++;
        i++;
    }
    gnuplotData->writeln(msgStat);
}

};
