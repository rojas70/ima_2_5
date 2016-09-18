Cartesian Controller

Dominant:

- DomCont_DesInput:	incremental cartesian move.
- DomCont_ActualInput:  No inputs. 
			1 Output.
			Will be bound to the HP3JC component. This will be the "output" binding for the cartesian component. 

Subordinate:

- SubCont_DesInput:	incremental cartesian move.
- SubCont_ActualInput = No inputs. 
			1 Output.
			Will be bound to the HP3JC component. This will be the "output" binding for the cartesian component.  

Projection:
- No projection will take place when a cartesian controller is selected. 
- There will be two separate outputs. The cartesian one will call IMOV from within this class. 
- The joint angle update will go to the ouput and then be moved when the state machine calls MOVJ.