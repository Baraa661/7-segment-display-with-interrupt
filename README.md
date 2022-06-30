# 7-segment-display-with-interrupt using stm32 
## A software to perform a decimal counter on a 7-segment display.
### System inputs:
* two push buttons.
### System output
* 1 seven segment display.
#### Two interrupts are be configured on GPIO falling edge, one for each button. The first ISR increments the counter. The second ISR decrements the counter. The main function perform the display actions. Race condition taken into consideration to protect the counters from being corrupted.
