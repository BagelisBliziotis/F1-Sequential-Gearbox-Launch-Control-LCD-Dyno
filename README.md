# F1 Sequential Gearbox + Launch Control + LCD Dyno

 Work in progress  hardware is wired, core logic is being finalized.

A desktop Formula 1 cockpit simulator built on Arduino. Inspired by real F1 start
procedures and gearbox behavior. This is one of the most complex projects I've built
so far  combining physical input hardware, a DC motor dyno, real-time LCD feedback,
and a multi-stage launch control sequence.

*What it does:
- Sequential gearbox — gear up/down via paddle shifters, with a clutch interlock
- Launch Control — mimics the real F1 start procedure: clutch in → hold RPM →
  clutch release → non-blocking RPM ramp up
- DC motor dyno — motor speed controlled via PWM, physically represents engine load
- 16×2 LCD dashboard — live display of gear, RPM, launch state, and system status
- RGB LED + gear LEDs — visual feedback via 74HC595 shift register
- Buzzer — audio cues for gear shifts and launch events
- Serial telemetry — real-time data stream to Serial Monitor
*Hardware:
| Component | Purpose |
 Arduino Uno / Main controller 
 16×2 LCD  / Live dashboard 
 DC motor + driver / Dyno simulation 
 74HC595 shift register / Gear indicator LEDs 
 RGB LED / System status 
 Passive buzzer / Audio feedback 
 Push buttons / Gear up, gear down, clutch 
 Potentiometer / Throttle input 

*Status:

- [x] Hardware wired
- [x] Initial code structure written
- [ ] Launch control ramp — finalizing
- [ ] LCD state logic — debugging
- [ ] Serial telemetry — testing
- [ ] Demo GIF — coming once stable

*What I'm learning:
This is my first project that combines mechanical simulation with real-time embedded
logic. Getting the launch control sequence right — non-blocking, with proper interlocks 
has been the hardest part. More in the final README once it's done.
