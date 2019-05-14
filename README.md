Thanks to inspiration from everyone at DC25!

Status:
Currently the rev1a board had a ~6 bad traces and had to be fixed.

Board rev1b has all of the traces fixed but I goobered up the pin layout for the Feather 328P.
  1. A couple bodge wires gets it up and running.
  2. I had to stop and laugh. I picked a feather because it has an onboard lipo charger.
     For some reason I had the bright idea to point the USB port at the battery.
     Basically, you can either plug in a battery or USB cable but not booth. Derp.
     Adding a $1.50 usb micro breakout board to the extra space on the feather gave me charging back!
Board rev1c will be finished after the Con. I'll post it up on PCBway if anyone wants to buy and build them.
I'll have the BOM and code here.

Update (end of 2018): Board Rev1C was completed and will be available as a kit shortly.

Update early 2019: I was seriously delayed in getting the board construction tutorial created along with releasing the board coding. I had intended to do a full re-write on the code. I've decided to simply post what was running at the conference instead of delaying the release. :-)

"ThursdayNight" is the code that ran on the badge during the conference. Some of you heard the story but I had a hard drive failure, while working on code, on our way to DEFCON. ThursdayNight was a rushed rebuild. It works well but some of the special effects I had written are gone. I hope to sit down and rewrite it again soon.

You'll need the DC26_Illuminati.cpp and DC26_Illuminati.h files allowing with installing the Adafruit_GFX.h library.

Thanks!
Kredence
