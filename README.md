<h1>PHGN481</h1>
<hr>

<h1>Senior Project - TIDLS Software</h1>

<hr>
<h2>Prototype tasks</h2>
<hr>

<h3>Complete</h3>
<hr>
<ul>
	<li>Basic user interaction</li>
	<li>Constants can be loaded from a text file</li>
	<li>Lifetime data can be loaded from a text file</li>
	<li>All necessary equation definitions are available for use</li>
	<li>Simulated lifetime data can be generated and exported to a text file for one or more defect txt files</li>
	<li>Loaded data can be analyzed and data for tn0, k, and chi^2 is exported</li>
</ul>

<hr>
<h3>Todo</h3>
<hr>
<ul>
    <li>Read temperatures used in data collection from file</li>
    <li>Change generated data output to match changes made in the data reading format</li>
    <li>Write/Use some plotting utilities</li>
</ul>

<hr>
<h3>Known issues</h3>
<hr>
<ul>
	<li>When loading data after a previous set of constants/data were loaded
		in the same session, the previous data is flushed for the new
		set of constants/data.  This may be undesirable behavior in the
		future.</li>
	<li>No validation of input values, some values passed to the generator will create an infinite loop.</li>
</ul>