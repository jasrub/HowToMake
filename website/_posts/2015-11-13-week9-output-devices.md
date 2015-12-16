---
layout: page
weekNum: "Week 9"
title: "Output Devices"
thumb: "images/week9/thumb1.jpg"
excerpt: ""
comments: false
share: false
---
 
### Light and Sound 
<figure>
	<img src="../images/week9/open.jpg" alt="image">
</figure>
 
This week's assignment was to add an output device to a microcontroller board we've designed and program it to do something.  
Since final assignments deadline is getting closer I'm trying to make things that I can use for my [final project](../week1-computer-aided-design/index.html) as well.  
I want my smart helmet to have LEDs on it, that will blink when I turn, and also a speaker inside, to give me directions.  So for this week's assignment I wanted to make a microcontroller board with a speaker and LED Array.

#### Board Design
I've looked at Neil's designs for [LED array board](http://academy.cba.mit.edu/classes/output_devices/array/hello.array.44.2.png) and a [speaker board](http://academy.cba.mit.edu/classes/output_devices/speaker/hello.speaker.45.png)
And combined them to a new board using Eagle.
I've added a button, a jack for power, and a green LED between VCC and ground that is turned on when the board is connected to power.
<figure>
	<img src="../images/week9/schematic.jpg" alt="image">
	<figcaption> My board Eagle schematic</figcaption>
</figure> 
<figure>
	<img src="../images/week9/board.jpg" alt="image">
</figure> 

All files for making the board can be [found here](https://github.com/jasrub/HowToMake/tree/master/files/week9/light_and_sound_board).  
  
The LED Array is done using 20 LEDs and only 5 pins with the great [Charlieplexing](https://en.wikipedia.org/wiki/Charlieplexing) technique.

Neil is using a nice trick in the LED Array to avoid the use of a lot of resistors and keep the board cleaner - 
There are 2 layers to the board, and they are separated with a vinyl-cut epoxy film sticker.
For doing this:  
You first mill the traces of the board as usual.  
Then, you vinyl-cut epoxy film and stick it on top of the board.  
The you vinyl-cut coper and stick it on top of the epoxy film.  
  
###### To create the vinyl cutting files in eagle:  
**The epoxy-film sticker:**  
When you are done designing the board hit *display none tCream*
Then go to view-> Layer settings and click on Change. Choose a solid filling for the tCream objects and export as a monochrome with 600 DPI
I then used Photoshop (But any simple paint software will work) to crop and invert the exported image.  
**Copper traces on top:**  
The important thing to remember here is that the vinyl cutter resolution is not the same as the milling machine's. **Use thicker lines**. The rest is easy, draw the traces on a different layer (I used bottom since I have the free version of Eagle and it only allows 2 layers) and export this layer only.  Again, invert and crop in any paint software.

#### Making the Board
Same process as making boards in the recent weeks. By now I got much better and faster in producing boards :)
(And an LED Array requires A LOT of soldering).  
<figure>
	<img src="../images/week9/milled_board.jpg" alt="image">
	<figcaption> First version of the board milled, you can see that the milling was not great</figcaption>
</figure> 
<figure>
	<img src="../images/week9/sticker.jpg" alt="image">
	<figcaption> putting the epoxy film sticker</figcaption>
</figure> 

<figure>
	<img src="../images/week9/with_copper.jpg" alt="image">
	<figcaption> And the copper traces</figcaption>
</figure> 
(On the first version of my board I added another black vinyl sticker, just for the color, this was a mistake since the vinyl melts under soldering heat.)

<figure>
	<img src="../images/week9/stuffed.jpg" alt="image">
	<figcaption> Stuffed board - second and better version</figcaption>
</figure>  

#### Programming the Board  
This is the fun stage of testing and playing around.
I first tested that each output device works by uploading Neil's code.
The LED Array was great:
<figure>
	<img src="../images/week9/array.gif" alt="image">
	<figcaption> LED array at action</figcaption>
</figure> 

The speaker was not that simple - when first uploading Neil's code nothing happened. 
(I suspected this was related to the fact the I used an Atitny 44 while Neil used Attiny 45 but did not succeed in debugging this, The code did compile and uploaded successfully to my board, now I'm thinking this was a power issue and I should test this again with a different power supply).
I then tried using Arduino Tone() library, but still, I heard nothing out of the speaker.  
After some reading around the web, I found [leah buechley's code for getting sound from a LilyPad](http://web.media.mit.edu/~leah/LilyPad/07_sound.html) and this magically worked.  

<iframe width="560" height="315" src="https://www.youtube.com/embed/PyxY3bH1KXU" frameborder="0" allowfullscreen></iframe>  

This was still not stable and the speaker would sometimes just click when I pressed to button. That issue eventually resolved by replacing the power supply to higher current (1 amp instead of 0.2). Next time I should add a resistor to the speaker to solve that.  
  
Then I had a lot of fun playing different 8 bit tunes I found online and composed my self, and lighting the LED's in different shapes
<figure>
	<img src="../images/week9/heart.jpg" alt="image">
	<figcaption> A blinking heart</figcaption>
</figure> 

<figure>
	<img src="../images/week9/arrow_blink.gif" alt="image">
	<figcaption> A moving arrow I can use on my helmet to signal turning direction</figcaption>
</figure> 


Eventually, I experimented with combining the light and sound output - I've created random lights that are show with each note of the annoying sound being played :)

<iframe width="560" height="315" src="https://www.youtube.com/embed/Foc7ZxowAzc" frameborder="0" allowfullscreen></iframe>

My code is a combination of Leah's sound_code and Neil's [hello.array.44.2](http://academy.cba.mit.edu/classes/output_devices/array/hello.array.44.2.c)
And it uses "pitches.h" from the Arduino Tone() Library.
[Get it here](https://github.com/jasrub/HowToMake/tree/master/files/week9/light_and_sound)

  
