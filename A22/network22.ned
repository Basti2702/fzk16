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
 	    nde[0].gate++ <--> {  delay = 100ms; } <--> nde[1].gate++;
        nde[1].gate++ <--> {  delay = 100ms; } <--> nde[2].gate++;
        nde[2].gate++ <--> {  delay = 100ms; } <--> nde[0].gate++;
}