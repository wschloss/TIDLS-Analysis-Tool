#CSM PHGN481/482 - Physics Senior Design

##TIDLS Data Analysis Tool

==============

## Description

Temperature and injection dependent lifetime spectroscopy attempts to identify the lifetime limiting defects in semiconducting wafers by analyzing the Shockley-Read-Hall lifetime.  Defects in semiconducting wafers are directly related to the efficiency of the cell in photovoltaic applications.  TIDLS analyzes SRH lifetime data as a function of injection level through a series of non-linear fits.  Solution space curves are built for the defining parameters k (symmetry factor) and tn0 (capture time constant for electrons) as functions of the guessed defect energy in the band gap.  Data at varying temperatures is analyzed to produce multiple curves, and their intersection occurs at the value for the defect energy that corresponds to the actual defect present.  For those interested in the full, detailed analysis of the method and its weaknesses, the final report for the project is included.

To analyze the data, we built this command line tool which generates SRH lifetime data from the theory and analyzes data sets to export k, tn0, and chi^2 as functions of guess defect level.  We plot the analyzed data to find intersections which indicate present defect levels.

#### Try it out...

The utility relies on the 'Minpack' library for non-linear fitting, and is provided along with a makefile to make compiling easy.  On a Unix system, run 'make' at the projects root directory to compile the executable 'TIDLS_nix'.  The executable is included if you have any issues.  Note that currently the temperatures for collected data are hardcoded in the analyzer since they correspond to the data received from the Sinton tool provided to us for the project.  This may be fixed at a future time, or you may change the temperatures and recompile, or generate data for the same range of temps that the Sinton tool provides (see our experimental data).

Generic data files are included in the 'src/dataFiles' directory, and include the constants, various defect parameters for generating data, and a set of real and generated lifetimes to use for analyzing.  The program requires you to load constants for generating data, and to load constants and data to analyze and export solution space data.  The format for each file must match the sample files provided.  For those interested in our results, our analysis is provided in the 'dataAnalysis' directory.