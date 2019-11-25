#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pipes import PipesControl 

def main():
    modules = dict()
    with PipesControl() as pipes:
        while True:
            r = pipes.readMessage()
            if r:
                try:
                    if (r['verbe'] == "hello"):
                        modules[r['source']] = { 'path': r['path'] }
                        pipes
                        
                except KeyError:
                    print("Message ignoré (", end='')
                    print(r, end='')
                    print(") !")
                    continue
                            
if __name__ == "__main__":
    main()