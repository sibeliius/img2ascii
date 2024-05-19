# img2ascii
Build instructions: 
>gcc -o [binary filename] img2ascii.c -lm 
>[binary filename] image

This program works in two main steps: converting the input image to grayscale and mapping the grayscaled image into an output textfile containing ASCII characters reflecting the varying gray values contained within each pixel of the image. It uses 