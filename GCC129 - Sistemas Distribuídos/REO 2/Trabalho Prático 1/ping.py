#  Mateus Carvalho Gonçalves - 201810245

import socket
import os
import time

udp_ip = "18.224.220.128"
udp_port = 6000
message = "ping"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.settimeout(0.25)
lost_packets = 0
rtt_list = []

for counter in range(10):
    try:
        rtt_start = time.time()
        
        sock.sendto(message.encode('utf_8'),(udp_ip, udp_port))
        data , addr = sock.recvfrom(1024)
        
        rtt_end = time.time()
        rtt = rtt_end - rtt_start
        rtt_list.append(rtt)

        print("Packet number", counter + 1, "received from", addr, "in", rtt, "second with message:", data.decode())

    except socket.timeout:
        lost_packets += 1

    time.sleep(1)


rtt_average = sum(rtt_list) / len(rtt_list)
print("Average RTT:", rtt_average, end='')
print("s")

packet_loss_rate = (lost_packets / 10) * 100
print(packet_loss_rate, end='')
print("%", "of packet loss")