
![](https://raw.githubusercontent.com/samuk/Sawppy_Rover/e5f680594240ed2d8a4927f3c0a8c97fe7f28924/modifications/Ag/photos/delta.png)

Keops would be nice, but kinematics obscure. Probably best to do arms instead.

![](https://raw.githubusercontent.com/Scottapotamas/zaphod-bot/master/docs/imgs/delta-render.jpg)

Use the mount plate and other mechanical components from the [Zaphod pictured above](https://github.com/Scottapotamas/zaphod-bot/tree/master#mechanics)

# Kinematics software 

- Developed from [eeduro](https://github.com/eeduro/delta)
  
# Reference Hardware
- 3X [BLDC motors in Nema23 format](https://odriverobotics.com/shop/odrive-custom-motor-d5065) each with [force of 208N](https://docs.google.com/spreadsheets/d/12vzz7XVEK6YNIOqH0jAz51F5VUpc-lJEs3mmkWP1H4Y/edit#gid=0)
- 3x [AMT212B encoder](https://odriverobotics.com/shop/cui-amt212b-v-od)
- 3x [Nema23 mount bracket](https://www.amazon.co.uk/STEPPERONLINE-Bracket-Precision-Alloy-Planetary/dp/B07SRXNSDC)
- [Base plate](https://github.com/Scottapotamas/zaphod-bot/blob/master/mechanical/design/manf_outputs/machining_proto/base_plate_light.STEP)
- [Bicep](https://github.com/Scottapotamas/zaphod-bot/blob/master/mechanical/design/manf_outputs/machining_proto/bicep2.STEP)
- [Bicep elbow](https://github.com/Scottapotamas/zaphod-bot/blob/master/mechanical/design/manf_outputs/machining_proto/bicep_elbow.STEP)
- [Carbon fibre arm](https://www.aliexpress.com/item/32952287433.html)
- [End effector/ hub](https://github.com/Scottapotamas/zaphod-bot/blob/master/mechanical/design/manf_outputs/printed_proto/proto_3/effector_3.STEP)

# Reference Electronics

- 2X [Twisted fields motor drivers](https://github.com/Twisted-Fields/rp2040-motor-controller#rp2040-motor-controller), [Firmware](https://github.com/Twisted-Fields/rp2040-motor-firmware#twisted-fields-rp2040-motor-controller-firmware), [interface](https://docs.simplefoc.com/commander_interface)
- 1x [AI-64](https://www.beagleboard.org/boards/beaglebone-ai-64)
- 1x [CanBus cape](https://www.beyondlogic.org/adding-can-to-the-beaglebone-black/) 
- 3x [TOF?](https://www.aliexpress.com/item/32958364902.html)

# Vision System
- [VGA TOF sensor?](https://github.com/lnsru/melexis_VGA_ToF_camera) [info](https://www.melexis.com/en/product/MLX75027/Gen3-VGA-time-of-flight-3D-camera)
- 2x Pi compatible camera into Ai-64?
- 1x [Luxonis Oak D?](https://shop.luxonis.com/products/1098obcenclosure)


## Laser actuators

~200g payload [Neje A40640 ~£200](https://neje.shop/products/40w-laser-module-laser-head-for-cnc-laser-cutter-engraver-woodworking-machine)
https://youtu.be/QrtGMzzSWDo?t=605

[A40640, 450nm ~10w, 220g](https://www.aliexpress.com/item/4001287562336.html)
[Cheaper Wavelength: 405nm](https://www.aliexpress.com/item/4000781652185.html)

[Cheaper 450nm ~5w](https://www.aliexpress.com/item/1005003640254307.html)
These components need to be assembled, tested & documented.


# Older notes / Misc

- Possibly handy Python kinematics https://github.com/ArthasMenethil-A/Delta-Robot-Trajectory-Planning
- 3x [3d print - corner.stl](https://openbuilds.com/builds/m3delta.1022/) for triangle - Todo
- Centrehub.stl ![](https://github.com/samuk/Sawppy_Rover/blob/main/modifications/Ag/centre.png?raw=true)
- 1x [3d print - plate.STL](https://www.thingiverse.com/thing:1249297/files) or [COTS](https://www.aliexpress.com/item/32707713574.html)
- 3X [Aluminum threaded bar/ carbon fiber arms](https://www.tunmaker.tn/2018/06/19/delta-robot-project/) 
- Toy: https://www.instructables.com/EEZYbotDELTA-3Dprinted-Robot/
- Kinematics on a microcontroller? https://github.com/tinkersprojects/Delta-Kinematics-Library
- 2X [Twisted fields drivers](https://github.com/jkirsons/stealth-controller)
- 3X [5010 motors](https://www.aliexpress.com/item/32517972556.html)
- 3X [Linear actuators](https://www.aliexpress.com/item/32838215862.html)
- 3X [IP65 Nema23 steppers](https://www.omc-stepperonline.com/waterproof-stepper-motor/p-series-ip65-waterproof-nema-24-closed-loop-stepper-motor-3nm-424-92oz-in-with-encoder-1000ppr-4000cpr.html) 
- 3X [Stepper drivers](https://www.aliexpress.com/item/32714985325.html)
and do BLDC later?
