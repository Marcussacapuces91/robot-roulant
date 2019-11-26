#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pipes import PipesControl
import subprocess

def main():
    modules = dict()
    with PipesControl() as pipes:
        print("Enregistrement des modules...")
        while True:
            r = pipes.readMessage()
            if r:
                try:
                    if (r['verbe'] == "hello"):
                        modules[r['source']] = { 'path': r['path'] }
                        print("Enregistrement du module {} avec le tube nommé {}.".format(r['source'], r['path']))
                        break
#                        pipes
                        
                except KeyError:
                    print("Message ignoré (", end='')
                    print(r, end='')
                    print(") !")
                    continue

        for k, m in modules.items():
            print(m)
            pipes.writeMessage(m['path'], { 'source': 'controle', 'verbe': 'fin' })
            

if __name__ == "__main__":
    
    main()