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
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Roal; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _DDWALKERMASTER_H_
#define _DDWALKERMASTER_H_



#include <unistd.h>
#include <RoalFramework/RoalCore.h>
#include <RoalFramework/Master.h>
#include <RoalFramework/LeggedCreaturePhenotype.h>
#include <RoalFramework/LeggedCreatureGenotype.h>


using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{

/** Helper Class */
class PhenotypeFitness {
    
/**
 * Overloaded operator.
 *
 * @param os The output stream.
 * @param message An instance of a ConnectorMessage to output.
 * @return The output stream.
 */
friend bool operator<(const PhenotypeFitness& left, const PhenotypeFitness& right);    
    
    public:
        PhenotypeFitness()
            {this->id = usedId; usedId++; inUse=false; fitness = 0;};
        int id; // unique in the system
        LeggedCreaturePhenotype* phenotype;
        float fitness;
        bool inUse;
    private:
        /**
         * used ids for the PhenotypeFitness object
         */
        static int usedId; 
};

/**Helper Strcut*/
struct PhenotypeResult {
    int id;
    float fitness;
};

/**
 * The Master implementation of the dynamic distributed walker example.
 *  
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */ 
class DDWalkerMaster : public Master
{
public:
    /**
     * Constructs an instance of Master.
     * 
     * Creates a Connector object that starts listening on a port and
     * waits for registration requests from slave nodes.
     */ 
    DDWalkerMaster(string ipAddress, int port, int poolsize, int parallelPhenotypeCnt);
    
    /**
     * Destructor.
     */
    ~DDWalkerMaster();

    /**
     * Starts the Master listening on a port.
     * 
     * @see Master::run
     */
    virtual void run();

private:
    
    void sendPopInitMessage(int sid, string agentName);
    /**
     * Default constructor, may not be used.
     */
    DDWalkerMaster();

    /**
     * A Genotype for the creatures of this Master.
     */
    LeggedCreatureGenotype* genotype;

    /**
     * A pool to hold the phenotyes.
     */
    list<PhenotypeFitness> phenotypes;

    /**
     * the required poolsize.
     */
    int poolsize;

    /**
     * this number defines how many creatures walker per agent.
     */
    int parallelPhenotypeCnt;

    /**
     * the method to fill up the pool of phenotyes.
     */
    void generatePhenotypePool();

    /**
     * the method to fill up the pool of phenotyes.
     */
    void handleSlaveResult(ConnectorMessage* msg);

    /**
     * the method to fill up the pool of phenotyes.
     */
    void updatePhenotypeInPool(int id, float fitness);

    /**
     * the method to fill up the pool of phenotyes.
     */
    void slaveResultsSort(PhenotypeResult* resultArray, int left, int right);

    /**
     * retunrs the phenotype of the given id
     */
    Phenotype* getPhenotype(int id);

    /**
     * crosses to phenotypes
     */
    void crossPhenotypes(int id1, int id2);

    /**
     * tdeletes a phenotype
     */
    void deletePhenotype(int id);

    /**
     * updates the Master stats
     */
    void updateStatistic();

    /**
     * number of genertations.
     */
    long genCount;

    /**
     * the gnupot config file.
     */
    File* gnuplotConfig;
    
     /**
     * the gnupot Data file.
     */   
    File* gnuplotData;

};

}

#endif //_DDWALKERMASTER_H_
