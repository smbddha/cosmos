#! /usr/bin/python3

import pygame

def main():
    bds = []

    pygame.init()
    pygame.display.set_caption('test program')

    screen = pygame.display.set_mode((640,480))
    screen.fill((0,0,255))

    running = True
    while running:
        for bd in bds:
            pygame.draw.circle(screen, (255,255,255), bd, 10, 0)
        
        pygame.display.update()

        for ev in pygame.event.get():
            if ev.type == pygame.MOUSEBUTTONUP:
                print(pygame.mouse.get_pos())
                bds.append(pygame.mouse.get_pos())
                print(bds)
            if ev.type == pygame.QUIT:
                running = False

if __name__=='__main__':
    main()
