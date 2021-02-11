# ArtSCII
Hello There! :)


i decided to write a simple program with __```C/C++```__, now let's have a look how does it work :)

# IMAGES
so at first let's have quick review how computers sotre an image:
- every image has 3 channel + 1 opcaity(alpha) channle which is optional:
    - RED Channel
    - GREEN Channel
    - BLUE Channel
    - alpha channel
- depend on the quality and bit depth (consider it as N) value of each chanell will be:
for example for 8 bit depth the possible values are between 0 and 256
$$
0 \leq Value < 2 ^{n} 
$$ 

# GRAYSCALE IMAGES
well, you may know that as black and whit classy image :)

but why we need it?

for showing image in form of ASCII characters, we need to take value of 1 channel, but the  question is wich channel?


if we convert our image to a grayscale image we will have only 1 channel which is density of each pixel, but how we can do that? there are several ways:

- __Average Method__: mean of RGB channels, this is not efficance way to cnovert a RGB image to grayscale altough for the first time i utilzed this method xD
- __Weigthed Method__ : convert an RGB to grayscale base on a formula for example
but the point is sum of cooficient must be equal to one:
$$
Density = 0.3R + 0.59G + 0.11B
$$
[for a simple example please follow this link :)](https://www.tutorialspoint.com/dip/grayscale_to_rgb_conversion.htm#:~:text=So%20the%20new%20equation%20that,and%20Blue%20has%20contributed%2011%25.)

# ASCII MAPPING
alright alright, now we have the density of each pixel the next move is how to convert our Numerical values to characters?

