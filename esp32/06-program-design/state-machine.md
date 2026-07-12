# State Machine

A state machine is a key way to organize ESP32 projects. It works well for buttons, mode switching, process control, and multi-step flows.

## 1. Core Idea

Split a program into states, and let the program run different logic in different states.

## 2. Example Scenarios

- Single click, double click, long press
- Idle, working, alarm
- Auto, manual, settings

## 3. Learning Goals

1. Know what a state is.
2. Know how states change.
3. Understand why this is easier to maintain than a pile of `if` statements.
