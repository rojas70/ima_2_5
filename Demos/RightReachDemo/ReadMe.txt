Right Reach Demo - Head Module to be opened in Sally and Arm Module to be opened in HungerForce 

Open the RightReachDemo - Popeye.cmp file in DAD.exe in HungerForce and
Open the RightReachDemo - Sally.cmp file in DAD.exe in Sally.

These files contain all that is necessary to run the demo. 

Attention! ***The component in Sally is the one that has the only and global State Machine.*** 
From the DemoStateMachine component in Sally, the agents in both computers will run. Just load and start the 
DemoStateMachine component under "RightReachDemo - Sally.cmp"

The Right Arm will ONLY generate a trajectory and execute it when: the numbers of pixels segmented
by the cameras exceed the threshold number (empirically calculated at 1250 pixels). After the reach is 
executed the arm will go back to the home position and test again for the condition.