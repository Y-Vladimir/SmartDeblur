SmartDeblur - with Blind Deconvolution 
===========
We are pleased to announce SmartDeblur 2.0.
This new release features a blind deblurring module which can automatically identify and remove complicated blur patterns in an image. Deblurring efficiency of the original version has also been improved.<br/>
See new web-site for project: <a href="http://smartdeblur.net">SmartDeblur.net</a><br/>
Example:
![Main Window 2.0](http://www.smartdeblur.net/example_main.jpg)

SmartDeblur 1.27 - old version
===========

SmartDeblur is a tool for restoring defocused and blurred images.
<br/>Written in C++ using Qt 4.8.
<br/>Algorithm based on several deconvolution techniques (Wiener, Tikhonov, Total Variation prior). Supported defect types are:
<ul>
    <li>Out of Focus blur (with kernel deep tuning)</li>
    <li>Motion blur</li>
    <li>Gaussian blur</li>
</ul>
SmartDeblur uses the FFTW library to provide its fast fourier tranformation implementation.
<br/>See <a href="http://fftw.org/">fftw.org</a> for details.
All source files are under the GPL v3 license.<br/>
<p>Author: <b>Vladimir Yuzhikov</b> (yuvladimir@gmail.com)

Detailed description of algorithms and methods you can see at my articles:<br/>
<a href="http://yuzhikov.com/articles/BlurredImagesRestoration1.htm">Restoration of defocused and blurred images (part 1) - Theory</a><br/>
<a href="http://yuzhikov.com/articles/BlurredImagesRestoration2.htm">Restoration of defocused and blurred images (part 2) - Practice</a><br/>


Sceenshots
==========
Main Window:
![Main Window](http://habrastorage.org/storage2/fb7/6ce/ee9/fb76ceee92de9cf664991fed9a54b0bc.png)

Features
========
<ul>
    <li>High speed. Processing a 2048*1500 pixel image takes about 300ms in the Preview mode (when
        adjustment sliders can move). But high-quality processing may take a few minutes
    </li>
    <li>Real-time parameters changes applying (without any preview button)</li>
    <li>Full resolution processing (without small preview window)</li>
    <li>Deep tuning of kernel parameters</li>
    <li>Easy and friendly user interface</li>
    <li>Help screen with image example</li>
    <li>Deconvolution methods: Wiener, Tikhonov, Total Variation prior</li>
</ul>

Download
========
Version 1.27: 
[SmartDeblur-1.27-win.zip](https://github.com/downloads/Y-Vladimir/SmartDeblur/SmartDeblur-1.27-win.zip)
[SmartDeblur-1.27-mac.dmg](https://github.com/downloads/gibbonweb/SmartDeblur/SmartDeblur-1.27-mac.dmg)

License
========
SmartDeblur is provided under the GPL v3 license
