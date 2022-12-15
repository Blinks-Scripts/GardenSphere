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
         ~Player direction ~  
         ~Fix inventory bugs ~   
         
12/13/22

Updates:
	Player Direction implemented; now represented by a carot showing player direction
	Inventory no longer crashes when empty;
	Depleted inventory items no longer display in the inventory
	
**Next up**:
	Loose Ends:
		Find candidates for encapsulation (player move methods can be consoldiated for example)
		Give classes proper accessor and mutator methods
		Improve .jfx file-structure - needs to be more intuitive - may need layers
		--> Down the road: make .jfx into animated ASCII sprites
		Begin implementing colors before it's too late. Visual design not necessary, but make sure everything knows how to have a color
		Items may need children classes for different item types
		
		Make a list of all code items to fix/ address before proceeding
		Create preliminary documentation
		
	**Down the road** :
		SCENARIOS: will include objectives and NPC routines
		-- Collisions need to be expanded to accomodate players, waypoints, objectives, etc
		Entering buildings



More to come
