float Utils::isHit(HANDLE phandle, uintptr_t clientbase)
{
    DWORD oldProtect = 0;

    int n = this->address;

    std::vector<BYTE> bytes = {
        0x45, 0x8B, 0x85, 0xF4, 0x01, 0x00, 0x00,
        0x44, 0x89, 0x05, 0xA5, 0x0F, 0x00, 0x00
    };

    /*
    std::vector<BYTE> jmpBytes = jmpTo(clientbase + 0x6a9d0da, clientbase+n); //code cave
    bytes.insert(bytes.end(), jmpBytes.begin(), jmpBytes.end());
 */
    std::vector<BYTE> jmpBytes = {0xE9, 0x4E, 0x19, 0x6A, 0xFC}; //modifie ici pour calculer le jump
    bytes.insert(bytes.end(), jmpBytes.begin(), jmpBytes.end());



    std::vector<BYTE> NOPs = { 0x90, 0x90, 0x90, 0x90, 0x90 };
    bytes.insert(bytes.end(), NOPs.begin(), NOPs.end());

    patchBytes((void*)(clientbase + 0x6a9d0cc), bytes.data(), bytes.size());




    std::vector<BYTE> jmp2 = {0xE9, 0x9A, 0xE6, 0x95, 0x03};//modifie ici pour calculer le jump
    std::vector<BYTE> data = { 0x90, 0x90 };
    jmp2.insert(jmp2.end(), data.begin(), data.end());
    patchBytes((void*)(clientbase + n), jmp2.data(), jmp2.size());





    float isBeingHit;
    uintptr_t isBeingHitAddress = clientbase + 0x6a9e07f;

    VirtualProtectEx(phandle, (LPVOID)(isBeingHitAddress), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
    ReadProcessMemory(phandle, (LPCVOID)isBeingHitAddress, &isBeingHit, sizeof(isBeingHit), NULL);

    if(isBeingHit > 0)
    {
        qDebug() << "hited";
    }
    qDebug() << isBeingHit;
    return isBeingHit;
}
