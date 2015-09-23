---
layout: page
title: "Week 2  :  Computer-Controlled Cutting"
excerpt: ""
comments: false
share: false
---

### Modular Honeycomb Shelves
The assignment this week was to design, make, and document a press-fit construction kit.  

I've recently moved to a new apartment and wanted to make some nice storage solution that
will be both pretty and functional.
My inspiration was the geometric simple design and infinity of honeycombs.  
  
I've used Rhino and Grasshopper to create the basic shapes the build hexagon boxes that can then build a honeycomb-like wall storage.  
My Grasshopper script gets as inputs the desired length of the hexagon sides, the thickness of the cardboard, and the laser offset. It is then outputs 3 shapes that I can send for printing (laser cutting)

The settings I've used with the Epilog laser cutter and given cardboard:  
speed: 25-29%  
power: 70-75%  
frequency: 25000  
Carbboard thickness: 4 mm  


<figure>
	<img src="../images/week2/design.jpg" alt="image">
	<figcaption>Planning with Rhino and Grasshopper</figcaption>
</figure>

The basic unit is made out of the base hexagon, that can connect with other base hexagons and creates the tiling; The squares, that connect to the base hexagon and create the walls; And the back part, which binds the whole part together and also has holes so it can be hanged on the wall.  
  
I've set the length parameter in my model to be 10cm, the fun thing is that I can now change this parameter and create the honeycomb shelves any size I'de like.

<figure>
	<img src="../images/week2/cut.jpg" alt="image">
	<figcaption>Laser cutting the parts</figcaption>
</figure>

<figure>
	<img src="../images/week2/pieces.jpg" alt="image">
	<figcaption>All parts, ready to be assembled</figcaption>
</figure>

<figure class="half">
	<img src="../images/week2/connecting.jpg" alt="image">
	<img src="../images/week2/construction.jpg" alt="image">
	<figcaption>connecting the pieces</figcaption>
</figure>

<figure>
	<img src="../images/week2/hanging.jpg" alt="image">
	<figcaption>Hanging on the wall</figcaption>
</figure>
<figure>
	<img src="../images/week2/finished_2.jpg" alt="image">
	<figcaption>Final result</figcaption>
</figure>
  
  
  

### Vinyl Cutting Fun

I've also got to play with the Vinyl Cutter machine this week.
I've made some fun stickers :)

<figure class="half">
	<img src="../images/week2/Vinyl1.jpg" alt="image">
	<img src="../images/week2/vinyl2.jpg" alt="image">
</figure>