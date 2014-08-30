PHGN481
=======

Senior Project - TIDLS Software


-------------------
Prototype tasks
-------------------

Complete:
- Basic user interaction
- Constants can be loaded from a text file
- Lifetime data can be loaded from a text file
- All necessary equation definitions should be available for use (Eqns used for simulated data are done, not tested)
- Simulated lifetime data can be generated and exported to a text file (Currently generates using the correct equations but incorrect constants since the constants list has wrong values)

Todo:
- Add additional equations necessary for fitting
- Generate data with the correct constants in place and plot in Mathematica to confirm the program reproduces the simulated lifetime/deltaN plots
- Loaded data can be analyzed and data for tn0, k, and chi^2 is exported
	-many possible subtasks here

Known issues:
- When loading data after a previous set of constants/data were loaded
	in the same session, the previous data is flushed for the new
	set of constants/data.  This may be undesirable behavior in the
	future.
