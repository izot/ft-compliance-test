# ft-compliance-test
This github repo implements a LonWorks communication performance test application using SNVT_count_32 variables to establish the performance baseline of the original Echelon FT-10 solution. The local EnOcean Nodebuilder project files are references as CommTest2.

## Purpose
- Evaluate Lon FT channel communication performance.
- Use `SNVT_count_32` based variables for transmit and receive counters.
- Track transmit failures and verify correct receive sequencing.
- Support long running test cases in excess of 100,000 packets

## Behavior
This UFPT defines the interface of the application. ![61 UFPTcommTester](images/CommTester_fb.png)
- At startup, a non-zero `cpUpdateRate` configures the node as a sender.
- Sender nodes increment output NV targets (`nvoTarget_1..nvoTarget_15`) using `testCount` values.  A sender only operates on nvoTarget_[n] values that are bound and does this in a round robin sequence.
- Receiving nodes validate that incoming `nviCount` values as successive single-unit increments.  
- Failed updates are counted and reported through `nvoFailCount`.
- Out of sequence errors are reported through `nvoFailCount`
- After cpTestLimit (100,000 default) nv updates, the sender stops the round robin increments of nvoTarget_[n]

## Key features
- Sender mode selection via `cpUpdateRate`.
- Broadcast of clear status messages before test messaging starts.
- Periodic pacing using application timers.
- Failure tracking for NV update failures.
- Receiver-side detection of out-of-sequence count values.
- Sending nodes verify the completion of an update before generating another update.

## Relevant files
- `CommTest2/commTester.nc` - main application logic for commTester functionality.
- `CommTest2/commTester.h` - component declarations and interface definitions.
- `CommTest2/common.h` - shared project definitions.


## Notes
- Senders are are devices that have bound connections to one or more nvoTarget_[n] outputs connected to a like devices nviCount input.  And the cpUpdateRate that is note zero.  2 should be considered the minimum (.2s)
- Receivers consider a missing or skipped count as a test failure and increment `failTotal`.
- The LonMark resource file set: apollo_dev.zip should be added to the test PC's types catalog if you are using IzoT Net Server.
- The IzoT CT Backup CTB_x_3RT.zip is the 61 device network including (16) FT-6050 Evb and (45) FT 3150 based devices used for baseline testing.  The connections use Ack'd service with 3 retries and default IzoT CT channel timing parameter.  Be sure to setup the Apollo_dev.typ file set before restoring the database.

## Baseline Testing
![61 Device Test Network](images/TestNetwork.png)
The system for the baseline test was configured using IzoT CT.  The operation of the test is done using nodeutil and the scripts found in the directory <b>Scripts</b> With the <b>Scripts</b> as the current working directory run:

## Quiet Wire Test
This test verifies the physical layer performance.  In this test, noteutil uses the performance test command with 0 retries to send an application message using code: 0x01.  The receiving node response message code 0x02 and the exact data that was received.

1. `nodeuitl -b -h -dx.default.rni -inodes.snu`
2. At the top nodeutil menu, type :`< cleancfg.snu` this will prevent any node from generating traffic.  All devices are setup as receivers.
3. Type: `< cleantest.snu>` this will send message code 0x01 and 10 bytes of data (hex encoded) 00 01 02 03 04 05 06 07 08 09.  The response code of 0x02 and the same data will be verified.  The is done for 1640 times to each of the networks 61 devices to generate roughly 100,000 message transactions.  At the end of the test, a passing grade is 0 errors.

## Peer-to-Peer Performance
In this test there are (16) sending devices that use Ack'd service with (3) retries to update each bound nvoTarget_[n] in a round robin fashion. Updates are offered only every 0.2 secondes by each of the senders.  At the start of the test the senders are reset, and there will be a random start where each sender boardcasts the clear status network diagnostic command to all devices on the channel. After each a total of `cpTestLimit` nv updatas are send, the sender stops generating traffic.  With all sender configured with the same `cpUpdateRate` (0.2s) and same `cpTestLimit` (100,000) the network traffic will drop from 70% BW utilization to 0 

1. `nodeuitl -b -h -dx.default.rni -isender.snu`
2. Type: `<peercfg.snu` this will set the sender devices `cpUpdateRate` to 0.2s.
3. Type: `<peertest.snu` this will reset the senders and after a short delay the test will run.  It is OK to exit nodeutil while the test runs for about the next 6 hours.  At the end of 6 hours, 1.6 million packets will have been send.  
4. Start nodeutil again: `nodeutil -b -h -dx.default.rni -ireport.snu -otestres.txt` This will add all (61) devices, poll the nvoFailCount value, and do a query status of each device in the system.  The results are capture in testres.txt.
