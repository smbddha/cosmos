#! /usr/bin/python3

import sys
import pygame
from time import sleep

dims = (1280,840)

def renormalize(n, range1, range2):
    delta1 = range1[1] - range1[0]
    delta2 = range2[1] - range2[0]
    return (delta2 * (n - range1[0]) / delta1) + range2[0]

def main():
    bds = []

    pygame.init()
    pygame.display.set_caption('test program')

    screen = pygame.display.set_mode(dims)
    screen.fill((0,0,255))

    N = int(sys.stdin.readline().strip()) 

    running = True
    while running:
        screen.fill((0,0,255))
        for n in range(N):
            x,y,vx,vy = map(lambda x: float(x), sys.stdin.readline().strip().split())
            x = int(renormalize(x, (-50e10, 50e10), (0, dims[0])))
            y = int(renormalize(y, (-50e10, 50e10), (0, dims[1])))
            #print(x,y)
            pygame.draw.circle(screen, (255,255,255), (x,y), 2, 0)
        
        pygame.display.update()

        for ev in pygame.event.get():
            if ev.type == pygame.MOUSEBUTTONUP:
                print(pygame.mouse.get_pos())
                bds.append(pygame.mouse.get_pos())
                print(bds)
            if ev.type == pygame.QUIT:
                running = False
        sleep(0.001)

if __name__=='__main__':
    main()
