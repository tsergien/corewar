.name "zork"
.comment "I'M ALIIIIVE"

	 sti r1 	,  		%:live	,	%1	

live:	live %1
		zjmp %:live
