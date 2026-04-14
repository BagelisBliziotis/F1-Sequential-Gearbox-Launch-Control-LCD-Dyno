# F1 Sequential Gearbox + Launch Control + Physical Dyno Simulator

Desktop Formula 1 cockpit simulato built on Arduino Uno. Features a realistic sequential gearbox with paddle shifters, clutch interlock, launch control sequence, physical DC motor
16×2 LCD dashboard, RGB status LED, gear-indicator Leds (74HC595 register), and buzzer feedback.

#Features:
- *Sequential 8-speed gearbox(N-1-2-3-4-5-6-7) with servo gear indicator
- *Clutch-paddle interlock – must hold clutch to shift 
- *Rev-match protection – downshift denied above 8500 RPM
- *Missed-shift detection with buzzer and warning
- *Launch Control – hold both paddles + clutch → arm → release clutch → automatic RPM ramp + dyno spin-up
- *Physical DC motor d – speed-controlled "engine" that reacts to throttle + gear + launch
- *Real-time 16×2 LCD dashboard – Gear , RPM , Throttle % , Speed
- *RGB + 8-LED gear strip via shift register
- *Serial telemetry (9600 baud) for monitoring

#Components:
- Arduino Uno
- 16×2 LCD (4-bit mode)
- Servo (gear indicator)
- 74HC595 + 7 LEDs (gear strip)
- RGB LED (status)
- Passive buzzer
- 10kΩ Potentiometer (throttle)
- 3x push buttons (clutch + up + down paddles) with internal pull-ups
- DC motor + driver (dyno)
- Breadboard + jumper wires
- 
#What i learned:
- Non-blocking state machines (`enum LaunchState`)
- Multi-component timing with `millis()`
- Shift register control (`shiftOut`)
- LCD + Servo + PWM integration
- Real-world F1 logic (clutch interlock, rev-matching, launch control)

