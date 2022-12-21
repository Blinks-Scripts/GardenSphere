Garden Game ( working title )

Currently in development.    


This readme will function more as a blog until the game has    
a more stable structure suitable for documenting.    

12/9/22    

Next up:    
~player movement~ DONE! for now...     
~player collisions to be added~ Collisions Complete!  
~map size increase~ Multiple tiles and moving between tiles supported!    

Down the road: implement SCENARIO class    

12/12/22    

Updates:    
Git repository re-hosted, still a learning curve there... 

Collisions implemented: player can no longer collide with buildings or impassable items...    
Buildings have edges defined by collision boxes (multiple possible per building)    
- building .jfx file contains parameters for collision boxes    
- collisions added to LOCATION object upon building creation            

COLLISIONS objects will be the "interface" between a player and a map coordinate     
- a map coordinate may contain an image (char) from a .jfx as well as an item stack,        
COLLISIONS are staged to offer additional fnctionality such as allowing doors to be entered,    
items to be destroyed, etc.    

Items/Inventory prototype added    
- Player can select an item from their inventory with the ']' key    
- Player can place selected item on the ground with the 'p' key    
- Player can pick up object beneath them with the 'g' key    
- Player can create am impassable !fence char with the 'o' key    
- **bugs**: depleted items still appear in inventory, placing a depleted item crashes game - *resolved*
          
Next Up:    
        ~Player direction~  
        ~Fix inventory bugs~   
         
12/13/22

Updates:
        Player Direction implemented; now represented by a carot showing player direction
        Inventory no longer crashes when empty;
        Depleted inventory items no longer display in the inventory
	
**Next up**:    
	Loose Ends:    
                ~Find candidates for encapsulation (player move methods can be consoldiated for example)~ 12/20: countless improvements, many candidates      
                   left such as the player object communicating to its location     
                ~Give classes proper accessor and mutator methods~ 12/20 partially complete, need to determine which accessors and mutators are necessary     
                   and which are simply going to make the code less readable. Need to figure out what methods should be public vs private, who the friends are    
                Improve .jfx file-structure - needs to be more intuitive - may need layers    
                ~--> Down the road: make .jfx into animated ASCII sprites~ 12/20 sprites and animation implemented, running into memory issues        
                   when trying to increase container space for sprite frames -- have to manually set frames container size instead of simply    
                   adding space for each frame. Please help!    
                Begin implementing colors before it's too late. Visual design not necessary, but make sure everything knows how to have a color    
                ~Items may need children classes for different item types~ 12/20 Maybe a better solution is to give them a pointer to special parameter?    
                Make a list of all code items to fix/ address before proceeding    
                Create preliminary documentation    
                
**Down the road** :    
        SCENARIOS: will include objectives and NPC routines    
        -- Collisions need to be expanded to accomodate players, waypoints, objectives, etc    
        Entering buildings  
        Learn markdown language better

12/20/22

**Updates:**
        Code was scoured line by line. The previous prototype was just that, a prototype laden with errors. This update is surely laden with errors as well, but it's much better. Issues were too numerous to list or even keep track of:    
        -PLAYER is now a 2 dimensional robot with tiny arms and a conveyor belt base!     
        -PLAYER is now an animated sprite!    
        -BUILDINGs now support animated sprites!    
        -BUILDINGs now support multiple collision boxes, meaning buildings can have complex collision shapes    
        -PLAYER position encapsulated into a POSITION object    
        -POSITION objects implemented - contain the WORLD_MAP and a LOCATION. PLAYER asks own POSITION for LOCATION : previously PLAYER had a LOCATION    
        -clock removed and replaced by TIMER. GAME will use a timer as the game clock, and individual objects such as the player or items may now have their own timers that function independently    
        -GAME run() logic reordered to make game experience smoother (no more advancing to the next frame too quickly)    
 
 **Next up**:
        -Building file is read every time a duplicate building is constructed with a new position, implement a copy constructor    
        -Implement colors    
        -Add documentation    


More to come
