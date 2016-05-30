//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package a22;

simple node
{
    parameters:
        int master = default(0);
        volatile double delayTime @unit(us);   // delay before sending back message
 	gates:
 	    inout gate[]; 
}

network a22net
{
    submodules:
 	   nde[3] : node;
 	connections:
 	    nde[0].gate++ <--> {  delay = nde[0].delayTime; } <--> nde[1].gate++;
        nde[1].gate++ <--> {  delay = nde[1].delayTime; } <--> nde[2].gate++;
        nde[2].gate++ <--> {  delay = nde[2].delayTime; } <--> nde[0].gate++;
}


network a22netcompound
{
    submodules:
        layer: Layer;
}


simple timestampsetter
{
 	gates:
	  inout gate[];
}



module Layer
{
 	submodules:
 	    node0: node;
 	    node1: node;
 	    node2: node;
 	    timestampsetter0: timestampsetter;
 	    timestampsetter1: timestampsetter;
 	    timestampsetter2: timestampsetter;
 	    
 	    connections:
 	        node0.gate++ <--> { delay = node0.delayTime; } <--> timestampsetter0.gate++;
 	        timestampsetter0.gate++ <--> node1.gate++;
 	        
 	        node1.gate++ <--> { delay = node1.delayTime; } <--> timestampsetter1.gate++;
 	        timestampsetter1.gate++ <--> node2.gate++;
 	        
 	        node2.gate++ <--> { delay = node2.delayTime; } <--> timestampsetter2.gate++;
 	        timestampsetter2.gate++ <--> node0.gate++;
 	          
}
