# Report

## How to run

You need to have installed SFML graphics library
https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/

Run
1. make
2. ./output


## Few notes

Since I decided to draw the graphics myself, there were a few things that I needed to do. 

1. Each rotation/action needed to be dissected into chunks/frames, so that the animation was smooth.

        This is why I used iterators to allow

            1. Specifying how many frames of the given animation is needed
            2. Making sure every set of animations is repeatable
            3. Allowing to step to the next frame whenever needed

2. I wanted to allow grouping animations together so that composing them is easier. 

        For this I created 3 types of movements.

            1. Basic movement: This is the smallest piece of movement. You use this to define a single rotation or something similar. You pass callback functions to actually define the behavior. 
                You also specify a target. It's just a number that will de divided into equal parts by the iterator, and on each step the divided number will be passed to the callback function.
                Mixing this kind of functional style with OOP might be considered distasteful, or wrong, but I decided that this is much easier to use this instead of for example creating a strategy for every single small action.

            2. Sequential movement: This one allows you to compose movements sequentially. When one is completed, the other one starts running. 

            3. Parallel movement: This one runs every movement that it has on each step. 

        This was so that it's possible to create animations with complex movements relatively easily. You can create simple groups of animations by using parallel or sequential movement. Then you can use these groups together to compose more complex movements again by grouping them in parallel or sequentially.

        For example for walking movement I have a sequence where the back leg femur rotates around the hip while also the tibia rotates around the knee while also the other leg is moving forward while the arms are also moving.

3. I wanted to make sure that when adding/modifying new segments to the body you wouldn't have to add code for your old animations to continue working. 

        For this I used composite pattern on the body segments. For example when you rotate the humerus around it's anchor (shoulder) the rest of the arm (radius, fingers) rotate too. In fact at first I didn't add fingers at all, but after adding them I didn't have to modify my animations, the rotations and shifts swill work.

        There is logic for correcting the small differences caused by floating point limitations on the length and angles of the body segments. The segments always stay the same size.

4. Having a composite for the body segments allowed me to use a visitor to go through the whole body and display each segment using it's own function. In this case there are only lines and a circle for the head.

5. I wanted to make sure that when the displaying starts, most of the calculations are already done and the sequence of animations is ready so that there are no pauses.


6. (Bonus) I made it so it's possible to change the speed of the animation and the scale of the body easily. You can change the defined SPEED and SCALE as needed.

## Known issues

1. A big one, I have a memory leak somewhere. You can find this if you set the speed to a small number (It works backwards) like 0.01, removing the shift parts from the animations so that the body stays in place and never reaches the object. And observing the memory usage. I tried to find it, but I haven't (yet). If I have more time before the deadline I will continue debugging this.

2. You might find my code too verbose or ugly or even bad at many places. I apologize for the absolute անգրագիտություն, I've pretty much never used c++ before this apart from solving small algorithmic problems. 

3. I have used new in some places that I needed dynamic memory (I don't think this is the thing that's causing the leak however). And I also used uniq_ptrs and immediately .release()-d them which essentially just defeats the point of using the uniq_ptr. But I did this just to define the basic animations inline instead of creating them separately, then adding them to movements.

4. I realize that I might have made this whole thing too comlicated for myself and overengineered it. Again, I apologise if it's hard to look at. 