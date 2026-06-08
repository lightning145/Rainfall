#ifndef TEXTURE_H
#define TEXTURE_H

unsigned int LoadTexture(const char* path);
void DeleteTexture(unsigned int texture);
void BindTexture(unsigned int texture, unsigned int slot);

#endif