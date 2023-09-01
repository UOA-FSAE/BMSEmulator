# BMSEmulator

#Timer Calculations
Because I felt like it only a single timer (TIM2) is used for timing the CAN messages. hopefuly this is ok.

Given a 48 MHz clock frequency, and the desired intervals of 48ms, 56ms, 104ms, and 152ms, we need to calculate the appropriate prescaler and compare values.

To start with, we need to configure the timer to overflow every 8ms, which will be our base interval.

Calculating the Prescaler and Overflow for 8ms:

$$
\text{Desired time base} = \frac{48 \times 10^6 \text{(cycles/second)}}{125 \times \text{(desired count for 8ms)}}
$$

Simplifying this, we get:

$$
\frac{125 \times \text{(desired count for 8ms)}}{48 \times 10^6 \text{(cycles/second)}} = 384,000
$$

For the Prescaler:

$$
\text{Prescaler} = \frac{48 \times 10^6 \text{(cycles/second)}}{384,000 \text{(cycles/8ms)}}
$$

Simplifying further:

$$
\frac{384,000 \text{(cycles/8ms)}}{48 \times 10^6 \text{(cycles/second)}} - 1 = 124
$$

I think this is correct?

Now, for the desired intervals, they translate to the following compare values:

    48ms => 48ms/8ms = 6 counts.
    56ms => 56ms/8ms = 7 counts.
    104ms => 104ms/8ms = 13 counts.
    152ms => 152ms/8ms = 19 counts.