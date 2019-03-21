#! /usr/bin/python3

import sys
import pygame
from time import sleep

def renormalize(n, range1, range2):
    delta1 = range1[1] - range1[0]
    delta2 = range2[1] - range2[0]
    return (delta2 * (n - range1[0]) / delta1) + range2[0]

def main():
    bds = []

    pygame.init()
    pygame.display.set_caption('test program')

    screen = pygame.display.set_mode((640,480))
    screen.fill((0,0,255))

    N = int(sys.stdin.readline().strip()) 

    c = 0
    running = True
    while running:
        print(c)
        c += 1
        for n in range(N):
            x,y,vx,vy = map(lambda x: float(x), sys.stdin.readline().strip().split())
            x = int(renormalize(x, (-10e9, 10e9), (0,640)))
            y = int(renormalize(y, (-10e9, 10e9), (0,480)))
            print(x,y)
            pygame.draw.circle(screen, (255,255,255), (x,y), 3, 0)
        
        pygame.display.update()

        for ev in pygame.event.get():
            if ev.type == pygame.MOUSEBUTTONUP:
                print(pygame.mouse.get_pos())
                bds.append(pygame.mouse.get_pos())
                print(bds)
            if ev.type == pygame.QUIT:
                running = False
        sleep(1)

if __name__=='__main__':
    main()
