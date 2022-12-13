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
***bugs: depleted items still appear in inventory, placing a depleted item crashes game    
          
Next Up:    
         Player direction    
         Fix inventory bugs    
         



More to come
