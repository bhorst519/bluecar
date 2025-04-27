## Message ID foramt
| bit possition | 10   | 9   | 8                                         | 7    | 6   | 5   | 4   | 3            | 2    | 1   | 0       |
| :------------ | :--- | :-- | :---------------------------------------- | :--- | :-- | :-- | :-- | :----------- | :--- | :-- | :------ |
|               | \|-- | --> | priority idx<br>(faster rate = lower idx) | \|-- | --- | --- | --> | message idx  | \|-- | --> | node ID |

## Node IDs by ECU
| ECU    | Node ID |
| :----- | :------ |
| EIM    | 0b000   |
| VCU    | 0b001   |
| TESTER | 0b111   |

## Priority guidelines
| ECU      | Priority idx |
| :------- | :----------- |
| Critical | 0b000        |
| 1kHz     | 0b001        |
| 100Hz    | 0b010        |
| 100Hz    | 0b011        |
| 10Hz     | 0b100        |
| 10Hz     | 0b101        |
| 10Hz     | 0b110        |
| 1Hz      | 0b111        |
