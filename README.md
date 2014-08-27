PHGN481
=======

Senior Project - TIDLS Software


-------------------
Prototype tasks
-------------------

Complete:
- Basic user interaction
- Constants can be loaded from a text file

Todo:
- All necessary equation definitions are available for use
- Lifetime data can be loaded from a text file (Walter is working on this)
- Simulated lifetime data can be generated and exported to a text file
- Loaded data can be analyzed and data for tn0, k, and chi^2 is exported
	-many subtasks here

Known issues:
- When loading constants after a previous txt of constants was loaded,
	constants with the same name will be overwritten, constants that don't
	have a new definition are not removed from memory, and constants without
	a previous definition are added to the data map.  This may be undesirable
	behavior in the future.
