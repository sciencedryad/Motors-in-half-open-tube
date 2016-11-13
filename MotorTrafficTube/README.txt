========================================================
PROGRAMS
========================================================

MotorSimulation.C
	standard MC motor lattice simulation: simulates 1 Markov chain,
	calculates averages in stationary state

TimeMotorSim.C
	for dynamics motor lattice simulation: calculates many Markov chains,
	calculates averages for each time step

analysis.C
	analysis time data from MotorSimulation.C for correlation functions
	and integrated correlation times,
	input files are binary Corr*,
	output files are ASCI Ana*,
	folder given interactively

TimeAna.C
	analises profiles from TimeMotorSim,
	calculates e.g. jam length

ConvertBIN2ASCI.C
	converts binary files to ASCI files
	input files: Corr* from interactively given folder
	out files: as infiles, with ASCI appended

DataCalc.C
	reads profiles from Res* files,
	does some calculations on them

FolderAna.C
	analyses data from different folders to
	give curves depending on parameters

========================================================
========================================================
CPP FILES
========================================================

========================================================
MOTOR SIMULATION
========================================================

Definitions.CPP
	definitions for motor simulations, libraries

Parameters.CPP
	Parameters for all Motor Simulations

TubeGlobals.CPP
	lattice class (tube geometry)

Particle.CPP
	Particle (motor) class

RandomMTImproved.CPP
	Mersenne twister random number generator

Globals.CPP
	global variables for MotorSimulation.C

GlobalsDynamics.CPP
	global variables for dynamic measurement (event currents)

Initialize.CPP
	inizialization for MotorSimulation.C

ReInitialize.CPP
	reinitialization after equilibration
	(for dynamic globals)

UpateBoundaries.CPP
	separate totally random boundary update for MotorSimulation.C
UpdateBoundariesSequential.CPP
	sequential separate boundary update for MotorSimulation.C
UpdateEachBoundaries.CPP
	separate random boundary update where each site is updated
	for MotorSimulation.C

UpdateMotors.CPP
	separate totally random motor update for MotorSimulation.C
UpdateEachMotor.CPP
	separate random motor update where each motor is updated
	for MotorSimulation.C

Update MotorsAndBoundaries
	random update of motors and boundary sites (at once)
	for MotorSimulation.C

Measure.CPP
	measurement for MotorSimulation.C

FinalMeasure.CPP
	final measurement for MotorSimulation.C

TimeInitialize.CPP
	Initialization for TimeMotorSim.C

TimeInitializeStep.CPP
	Initialization for one random number seed run
	for TimeMotorSim.C

TimeMeasure.CPP
	Measurement for TimeMotorSim.C

TimeFinalStep.CPP
	final step of run with fixed seed
	for TimeMotorSim.C

TimeFinalMeasure
	final measurement for TimeMotorSim.C

MotorSubroutines.CPP
	subroutines for MotorSimulation.C
	(create, destroy, update boundary, read / write configuration)

========================================================
DATA ANALYSIS
========================================================
ana.CPP
	subroutine to correlation function, integrated correlation time

DataCalcSubroutines
	subroutines for DataCalc.C
