PHGN481
=======

Senior Project - TIDLS Software


-------------------
Prototype tasks
-------------------

Complete
-------------------

FUNCTIONALITY:
- Basic user interaction
- Constants can be loaded from a text file
- Lifetime data can be loaded from a text file
- All necessary equation definitions should be available for use (Eqns used for simulated data are done)
- Simulated lifetime data can be generated and exported to a text file

GUI:
-Basic layout created

-------------------------
Todo
-------------------------

FUNCTIONALITY:
- Add additional equations necessary for fitting
- Loaded data can be analyzed and data for tn0, k, and chi^2 is exported
	-many possible subtasks here

GUI:
-Link GUI buttons to our implemented functionality
-Begin drawing of graphs after analyzing has been implemented

-------------------------
Known issues
-------------------------
- When loading data after a previous set of constants/data were loaded
	in the same session, the previous data is flushed for the new
	set of constants/data.  This may be undesirable behavior in the
	future.
- No validation of input values, some values passed to the generator will create an infinite loop.
-GUI Layout and sizing should be refactored to use wxWidgets sizer classes
