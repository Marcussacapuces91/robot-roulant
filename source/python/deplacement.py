#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pipes import Pipes

            
if __name__ == "__main__":
    modules = dict()
    with Pipes("/tmp/controle") as pipes:
        while True:
            r = pipes.readMessage()
            if r:
                try:
                    if (r['verbe'] == "hello"):
                        modules[r['source']] = { 'path': r['path'] }
                except KeyError:
                    print("Message ignoré (", end='')
                    print(r, end='')
                    print(") !")
                    continue
                
                print(modules)
                
#            else:
#                break
