# Fragment AS Reboot
 This is a full reboot of the .Hack//Fragment Area Server... With the aim of create a uncapped root town that handles area instances for parties of 3 through a subserver architecture... and impliment admin functions beyond kick/ban as no such functions where originally implemented on the AS.

 ## DevStack
 1. C++ (SDL2/Image/Net)                _Root Town Server_
 2. NPM + NodeJS (Mesh-Link, ExpressJS) _Party & Dungeon Handling_

 ## TODO
 1. Make Window to mimic Official AS (doesnt have to be exact).
 2. Get Area Server to List on Lobby Server (Official AS Ip: "a.dothackers.org")
 3. Handle Inbound Connections
 4. Uncapped Root Town + Instanced Dungeons

 ## Known Information
 1. The lobby server hosts it's own webAPI that lists servers' status' at "a.dothackers.org:5010/status". 5000 is API and 49000 is Server
 2. https://www.dothackers.net/forums/viewtopic.php?t=17240 (some very useful information on the networking side of things)
 ![Alt text](InfoDocs/Fragment%20Binary%20Message%20Framing%20-%200.png?raw=true "Fragment Binary Message Framing - 0")
 ![Alt text](InfoDocs/Fragment%20Binary%20Message%20Framing%20-%201.png?raw=true "Fragment Binary Message Framing - 1")
