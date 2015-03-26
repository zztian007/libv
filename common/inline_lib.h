// some inline library functions
// strlen
unsigned char lib_m[] =
{
	0x83, 0xC9, 0xFF, // or ecx, -1
	//0x8B, 0x38,	// mov edi,[eax]
	0x33, 0xC0,	// xor eax,eax
	0xF2, 0xAE,	// repne scas [edi]
	0xF7, 0xD1,	// not ecx
	//0x49 // dec ecx
};

// strcpy
unsigned char lib_m2[]=
{
	0x33,0xC0, // xor eax, eax
	0x8A,0x88,0xF4,0x20,0x0B,0x01,// f:mov cl, byte ptr [eax+10B20F4]
	0x88,0x0C,0x04,// mov [eax+esp],cl
	0x40,// inc eax
	0x84,0xC9,//test cl,cl
	0x75,0xF2 // jnz f
};

// div 9
unsigned char lib_m3[]=
{
	//0x8B,0x4C,0x24,0x04,//mov ecx,dword ptr [esp+4]
	//0xB8,0x39,0x8E,0xE3,0x38, // mov eax, 38E38E39
	0xF7,0xE9,// imul ecx
	0xD1,0xFA,// sar edx,1
	0x8B,0xC2,//mov eax,edx
	0xC1,0xE8,0x1F,//shr eax,1F
	0x03,0xC2,//add eax,edx
};

// _pos_end
unsigned char lib_m4[]=
{
	0x8A,0x08, // mov cl, byte ptr [eax]
	0x40, // inc eax
	0x84,0xC9, // test cl,cl
	0x75,0xF9, // jnz ...
};

// strcpy version 2
unsigned char lib_m5[]=
{
	//0x8B,0xC8,// mov ecx,eax
	0xC1,0xE9,0x02, // shr ecx,2
	//0x8B,0xF2, // mov esi,edx
	0xF3,0xA5,// rep movsd
	0x8B,0xC8,// mov ecx,eax
	0x83,0xE1,0x03,//and ecx,3
	0xF3,0xA4// rep movsb
};
// strcat
unsigned char lib_m6[]=
{
	0x56, // push esi
	0x57, // push edi
	0x8D,0x7C,0x24,0x08,// lea edi,[]
	0x2B,0xC2, // sub eax,edx
	0x4F // dec edi
};

// strcmp
unsigned char lib_m7[] =
{
	0x8A, 0x0A, // mov     cl, [edx]
	0x3A, 0x08, // cmp     cl, [eax]
	0x75, 0x1A, // jnz     short loc_401042
	0x84, 0xC9, // test    cl, cl
	0x74, 0x12, // jz      short loc_40103E
	0x8A, 0x4A, 0x01, // mov     cl, [edx+1]
	0x3A, 0x48, 0x01, // cmp     cl, [eax+1]
	0x75, 0x0E,               //              jnz     short loc_401042
	0x83, 0xC2, 0x02,          //                add     edx, 2
	0x83,0xC0,0x02,               //           add     eax, 2
	0x84,0xC9,                   //          test    cl, cl
	0x75,0xE4,                   //          jnz     short loc_401022
	0x33,0xC0,            //                 xor     eax, eax
	0xEB,0x05,              //               jmp     short loc_401047
	0x1B,0xC0,              //               sbb     eax, eax
	0x83,0xD8,0xFF           //               sbb     eax, 0FFFFFFFFh
};

// abs
unsigned char lib_m8[] =
{
	0x8B,0x44,0x24,0x08,// mov eax,[]
	0x99,// cdq
	0x33,0xC2, // xor eax,edx
	0x2B,0xC2 // sub eax, edx
};

// memcmp
unsigned char lib_m9[] =
{
	0x8B,0x0A, // mov ecx,[edx]
	0x3B,0x08,//cmp ecx, [eax]
	0x75,0x0E,// jne
	0x83,0xEE,0x04,// sub esi,04h
	0x83,0xC0,0x04,// add eax,04h
	0x83,0xC2,0x04,//add edx,04h
	0x83,0xFE,0x04,//cmp esi,04h
	0x73,0xEC,//jnc 
	0x0F,0xB6,0x38,//movzx edi, byte ptr ds:[eax]
	0x0F,0xB6,0x0A,//movzx ecx, byte ptr ds:[edx]
	0x2B,0xCF,//sub ecx, edi
	0x75,0x27,//jne
	0x0F ,0xB6 ,0x4A,0x01,// movzx ecx,byte ptr ds:[edx+01h]
	0x0F ,0xB6 ,0x78 ,0x01,// movzx edi,byte ptr ds:[eax+01h]
	0x2B ,0xCF,// sub ecx,edi
	0x75 ,0x1B,//jne
	0x83 ,0xFE ,0x02,//cmp esi,02h
	0x76 ,0x31,// jbe
	0x0F ,0xB6 ,0x4A ,0x02,// movzx ecx, byte ptr ds:[edx+02h]
	0x0F ,0xB6 ,0x70 ,0x02 ,// movzx esi, byte ptr ds:[eax+02h]
	0x2B ,0xCE,// sub ecx,esi
	0x75 ,0x0A,// jne
	0x0F ,0xB6 ,0x4A ,0x03,// movzx ecx, byte ptr ds:[edx,+03h]
	0x0F ,0xB6 ,0x50 ,0x03 ,// movzx edx,byte ptr ds:[eax+03h]
	0x2B ,0xCA,// sub ecx,edx
	0xC1 ,0xF9 ,0x1F,// sar ecx,1fh
	0x83 ,0xC9 ,0x01, // or ecx,01h
	0x74 ,0x13 // je 
};
// strlen2
unsigned char lib_m10[] = {
	//0x8D, 0x04, 0x24, 0x8D, 0x50, 0x01,
	0x8A, 0x08, // mov cl, byte ptr [eax]
	0x40, // inc eax
	0x84, 0xC9, // test cl, cl
	0x75, 0xF9, // jne 
	0x2B, 0xC2 // sub eax, edx
};

// strset
unsigned char lib_m11[] = {
	0x80, 0x3C, 0x24, 0x00, 0x8D, 0x04, 0x24, 0x74, 0x09, 0xC6, 0x00, 0x01, 0x40, 0x80, 0x38, 0x00, 
	0x75, 0xF7
};

// wcscat
unsigned char lib_m12[] = {
	0x8B, 0xD0, 0x8B, 0xFF, 0x66, 0x8B, 0x08, 0x83, 0xC0, 0x02, 0x66, 0x85, 0xC9, 0x75, 0xF5, 0x53, 
	0x56, 0x57, 0x8D, 0x7C, 0x24, 0x0C, 0x2B, 0xC2, 0x83, 0xC7, 0xFE, 0x8D, 0x5F, 0x02, 0x8D, 0x9B, 
	0x00, 0x00, 0x00, 0x00, 0x66, 0x8B, 0x4F, 0x02, 0x83, 0xC7, 0x02, 0x66, 0x85, 0xC9, 0x75, 0xF4, 
	0x8B, 0xC8, 0xC1, 0xE9, 0x02, 0x8B, 0xF2, 0xF3, 0xA5, 0x8B, 0xC8, 0x83, 0xE1, 0x03, 0xF3, 0xA4
};

// eax?-1:0
unsigned char lib_m13[]=
{
	0xF7,0xD8,0x1B,0xC0
};
