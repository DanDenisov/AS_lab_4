
(AxisLength: 36 cm, 2000 units)
(Translation: 2000 / 36 * 10 = 555.56 real-units)
(DriveSpeed: 24 * 145 / 60 = 58 real-units/s)
(AxisSpeed: 6500 virtual-units/s)
(Hence, Translation [virtual-units] = AxisSpeed / DriveSpeed * Translation [real-units] = )
( = 6500 / 58 * 555.56 = 62260 virtual-units)

%001 (CncProgram)
N05 G90
N10 F390000
N20 G01 X0 Y62260 Z0
N30 G01 X0 Y62260 Z62260
N40 G01 X62260 Y0 Z62260
N50 G01 X0 Y0 Z62260
N60 G01 X0 Y0 Z0
N999 M30
