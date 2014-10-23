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
#ifndef _NNWALKERAGENT_H_
#define _NNWALKERAGENT_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <list>
#include <vector>
#include <fann.h>

#include <RoalFramework/RoalCore.h>
#include <RoalFramework/DistributedAgent.h>
#include <RoalFramework/Box.h>
#include <RoalFramework/LeggedCreatureFactory.h>
#include <RoalFramework/LeggedCreatureGenotype.h>
#include <RoalFramework/LeggedCreaturePhenotype.h>
#include <RoalFramework/LeggedCreatureBrain.h>

using namespace std;

/**
 * Roal, Research Objective: Artificial Life
 */
namespace Roal
{
//class DistributedWorld; // Forward declaration for World class

/**
 * A struct used in NNWalkerAgent to generate a pool of creatures, rated by the NN.
 */
struct PhenotypeFitness {
    LeggedCreaturePhenotype* phenotype;
    float fitness;
};

/**
 * The Agent implementation for the neural network walker example NNWalker.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 */
class NNWalkerAgent : public DistributedAgent
{
public:
  
    /**
     * Constructor with additional parameters.
     * 
     * @see Agent::Agent
     * 
     * @name The name of the agent
     * @param world The World which holds this Agent
     * @param populationSize The number of creatures
     * @param generationCycle The life time of a generation in seconds
     * @param newOriginPosition The origin position where to place the creatures around
     * @param genotype A genotype to use for creatures the Agent generates.
     * @param collectTrainingDataMode If true, collect data for FANN training file
     * 
     * @see NNWalkerAgent::collectTrainingDataMode
     */
    NNWalkerAgent(const std::string name, DistributedWorld* world,
                  int populationSize, int generationCycle,
                  Position* newOriginPosition,
                  LeggedCreatureGenotype* genotype,
                  bool collectTrainingDataMode=false);
    
    /**
     * Create and register the creatures.
     *
     * This method is only use from the constructor.
     */
    void initPopulation();
    
    /**
     * @see Agent::handleMutate
     */
    void handleMutation();

protected:
    /**
     * This is the origin position of the Agent.
     */    
    Position* originPosition;
    
    /**
     * @see Agent::populationSize
     */
    int populationSize;
    
    /**
     * Train a neural network from a given datafile and save it.
     * 
     * @param dataFile The FANN training file
     * @param netFile The file that will be created and will contain the data
     *                of the trained neural network (FANN).
     */
    void trainNeuralNetwork(string dataFile, string netFile);
    
    /**
     * Generates a (sorted) pool of phenotypes and predicts their fitness with a NN.
     * 
     * @param phenotypesPoolSize The amount of Phenotypes that will be created.
     * @param The FANN file with the data of a trainied NN to rate the phenotypes.
     */
    list<PhenotypeFitness> generatePhenotypePool(int phenotypesPoolSize,
                                                 string netFile);
    
    /**
     * Elect the best phenotypes, create Body and Brain and register them.
     * 
     * @param phenotypes The phenotype pool from which the best ones are elected
     *                   and registered in the World.
     * @param numberOfPhenotypes The amount of phenotypes that will be elected
     *                           (has to be lesser than the amount of phenotypes
     *                           in the pool.
     */
    void electAndRegisterPhenotypes(list<PhenotypeFitness> phenotypes,
                                    int numberOfPhenotypes);
    
    /**
     * Sorts an array of Brain objects by their fitness.
     * 
     * @param brainsArray An array of Brain objects.
     * @param left The index of the left border (0 if from beginning).
     * @param right The index of the right border (size of brainsArray if until end).
     */
    void distancesSort(LeggedCreatureBrain** brainsArray, int left, int right);
    
private:
    /**
     * Default constructor, may not be used.
     */
    NNWalkerAgent();
    
    typedef std::map<int, Brain*> BrainsContainer;
    /**
     * The Brain objects
     */
    BrainsContainer brainsCon;
    
    typedef std::map<int, Body*> BodiesContainer;
    /**
     * The Body objects
     */
    BodiesContainer bodiesCon;
    
    /**
     * An instance of the LeggedCreatureFactory, used to generate random phenotypes.
     */
    LeggedCreatureFactory* factory;
    
    /**
     * A Genotype for the creatures of this Agent.
     */
    LeggedCreatureGenotype* genotype;
    
    /**
     * The size of the pool of phenotypes.
     * 
     * The pool contains the phenotypes that are rated by the NN and from which
     * the best rated phenotypes are elected for the simulation.
     */
    int phenotypesPoolSize;
    
    /**
     * The amount of phenotypes that are elected from the pool.
     * 
     * @see NNWalkerAgent::phenotypesPoolSize
     */
    int electedPhenotypes;
    
    /**
     * If true, collect data for FANN training file
     * 
     * Training data mode collects data of random creatures and writes them to
     * a data file that will be used to train the neural network (i.e. when not
     * in collectTrainingDataMode).
     */
    bool collectTrainingDataMode;
    

};


}

#endif //_NNWALKERAGENT_H_
