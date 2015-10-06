# CH-926 Arduino

I recently had to use a CH-926 coin acceptor (made by [Sintron](http://www.sintron-hk.com/CH-926-intelligent-multi-coin-acceptor-for-6-kinds-of-coins-P2711303.aspx)) in an [Arduino project](https://github.com/changeforchange/) that accepted coins for instant donations to charity using [JustGiving](https://github.com/changeforchange).

I had many problems with programming the device in the first place to accept coins and then spent hours trying to find a way to process the signal from the coin acceptor.

So here is a little guide on how to get the coin acceptor setup and some sample code you can use in your projects.

I'm hoping to eventually turn this into a Arduino Library.

*Note: The code included in this project was designed to work with my specific unit of the CH-926. Other sample code online didn't work for me so I can't guarantee this will work for you as I may have a faulty unit that works differently.*

If you have any questions or suggestions you can contact me on Twitter [@DavidMaitland](https://twitter.com/davidmaitland).

## Device configuration

### Wiring

- **DC12V** (Red) Goes to your 12v supply.
- **COIN** (White) Goes to pin A1 on your Arduino (this outputs 5v).
- **GND** (Black) Goes to your **common** ground, yes it needs to ground on both your Arduino and the 12v power supply.
- **COUNTER** (Grey) Leave it alone, ain't got a clue what it's for.

### Switches

- Set the top switch to **NC** (this should be the down position).
- Set the speed switch to slow (this can be changed, but it's what I used).

### Setup

*I may include a device programming guide in the future, but I did follow the terrible instructions and got it working (after 7 attempts). The reset function will be your friend.*

Pay attention to the pulse setting when progarmming your coins. In this code the `signalCostFactor` is 5 (you can change this). Which means each pulse is worth 5p, so when progarmming the 5p you would have it send 1 pulse, 10p would send 2, 20p would send 4 and so on..

## Usage

If you have programmed the coin acceptor and completed the device configuration above you should be ready to go.

Open and upload the script (`CH-926-Arduino.ino`) to your Arduino (I used a Arduino Uno). Open the serial monitor (9600 baud) and you should see the following when you insert coins...

```
Ready..
Coin Value: 10
Balance: 10
Coin Value: 20
Balance: 30
Coin Value: 20
Balance: 50
Coin Value: 5
Balance: 55
```

There is an issue with the coin value, if coins are inserted within the debounce delay of each other they will become one. This doesn't affect the balance but you may get some 30p coin values if say a 10p & 20p were inserted at quick succession. If this is a problem for you try changing the debounce delay to be shorter and the speed switch on the coin acceptor to be faster. I never got around to trying this.
