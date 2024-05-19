Build instructions: 
>gcc -o [binary filename] img2ascii.c -lm

>[binary filename] image

This program works in two main steps: converting the input image to grayscale using the luminosity method and mapping the grayscaled image (using a standard grayscale ASCII character ramp) into an output textfile, where the image is represented using ASCII characters. 

#### Note that the current resulting ASCII output is PROPORTIONAL to the input image dimensions. 
You can combat this by preemptively downscaling an input image if you want it to be a more digestible size. In the future I plan to add customizable resampling options.

WIP features:
- Allow a user to input their own custom ASCII ramp as a string or in a txt file
- Bilinear/bicubic algorithm implementations to resample the current large ASCII output.
