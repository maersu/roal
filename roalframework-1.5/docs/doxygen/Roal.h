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

/*! @mainpage Roal Framework (Research Objective: Artificial Life)     
 *  
 * Roal is a free software project that aims to provide a framework for the
 * development of simulations (in C++) in the field of artificial intelligence
 * (AI) and artificial life (AL). It contains example simulations that use the
 * framework and highlight its potential. In the simulations, artificial life
 * forms act in a virtual 3D environment with a realistic physical behavior. The
 * framework integrates common AI/AL techniques like evolutionary programming,
 * genetic algorithms and artificial neural networks and provides a distributed
 * architecture, alowing to run a simulation on multiple hosts.
 * 
 * @image html screenshot.png
 * @image latex screenshot.ps
 * 
 * @section mot Motivation
 * At the heart of artificial intelligence research are basic questions: What is
 * intelligence?  When is something or somebody intelligent? What is intelligent
 * behavior?
 * 
 * Artificial life is a subfield of artificial intelligence. Its purpose is to
 * study life through the use of human-made analogues of living systems. This is
 * often done by constructing models of the reality and may involve methods from
 * biology like Darwin's theory of evolution by natural selection. 
 * 
 * @section impl Implementation
 * With Roal we create a world that offers the virtual environment in which
 * artificial life simulations take place. This world has physical characteristics
 * that can be specified and that shape the creatures' behavior. The artificial
 * life forms (or organisms) and other objects can be created and put into the
 * world. We focus on life forms that have bodies consisting of multiple segments
 * connected through various types of joints, but the framework does not restrict
 * the character and the type of life forms or machines. The body of the life form
 * is equipped with different types of "sense organs" that are sensitive to,
 * e.g., light, color, or physical contact. These sensors send their actual state
 * to the creature's brain, which may be an artificial neural network (ANN) or
 * a similar method.
 * 
 * The brain controls the body through effectors. It may, for example, apply a
 * torque to one of the creature's joints. Roal then uses the functionality of
 * the ODE physics engine to compute the resulting effect on other parts of the
 * body and elements in the virtual environment. The graphical output is produced
 * with the 3D engine Ogre and the underlying OpenGL technology.
 * 
 * In order to be able to use more computing resources, a simulation can be
 * distributed to multiple systems.
 * 
 * The bodies and the knowledge of life forms can adapt to or learn from new
 * situations and the environment (e.g., a life form with an advanced body and a
 * sophisticated mind/knowledge may emerge from an evolutionary process). Typical
 * simulations that can be created with the Roal framework define a goal the
 * creatures strive for. This may be walking, swimming, foraging, or another target.
 * We can imagine simulations like a football game with multiple adaptive creatures
 * or a simulation of life forms that evolve and adapt to the current environment.
 * Even computer aided design where virtual furniture is created with artificial
 * intelligence is a potential application. 
 *
 * @section info_sec More Information
 * You can find more information about the project on the
 * <a href="http://roal.sourceforge.net/" target="_blank">Project Wiki</a> or on the 
 * <a href="http://sourceforge.net/projects/roal/" target="_blank">SourceForge Project Site</a>.
 * 
 * @author Hofer Mathis <a href="mailto:hofem2@hti.bfh.ch">hofem2@hti.bfh.ch</a>
 * @author Marcel Eyer <a href="mailto:eyerm@hti.bfh.ch">eyerm@hti.bfh.ch</a>
 * 
 */
