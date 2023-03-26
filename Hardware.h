#include <stdint.h>
#include <windows.h>      
#include <intrin.h>       
#include <iphlpapi.h>    
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
using namespace std;
uint16_t ma1;
uint16_t ma2;	

uint16_t hashMacAddress( PIP_ADAPTER_INFO info )          
{        
   uint16_t hash = 0;          
   for (uint32_t i = 0; i < info->AddressLength; i++ )   
   {     
      hash += ( info->Address[i] << (( i & 1 ) * 8 ));        
   }     
   return hash;           
}        

void getMacHash( uint16_t& mac1, uint16_t& mac2 )              
{        
   IP_ADAPTER_INFO AdapterInfo[32];                  
   DWORD dwBufLen = sizeof( AdapterInfo );           

   DWORD dwStatus = GetAdaptersInfo( AdapterInfo, &dwBufLen );                  
   if ( dwStatus != ERROR_SUCCESS )                  
      return; // no adapters.      

   PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;      
   mac1 = hashMacAddress( pAdapterInfo );            
   if ( pAdapterInfo->Next )       
      mac2 = hashMacAddress( pAdapterInfo->Next );   

   // sort the mac addresses. We don't want to invalidate     
   // both macs if they just change order.           
   if ( mac1 > mac2 )     
   {     
      uint16_t tmp = mac2;     
      mac2 = mac1;        
      mac1 = tmp;         
   }     
}        
bool isValidMD5(std::string value){
	if (value.size() == 32 && value.find_first_not_of("0123456789abcdefABCDEF") == -1)
		return true;
	else
		return false;
}
int getVolumeHash()       
{        
   DWORD serialNum = 0;   
   
   GetVolumeInformation( "c:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0 );    
   int hash = (int)(( serialNum + ( serialNum >> 16 )) & 0xFFFF );              

   return hash;           
}        

uint16_t getCpuHash()
{        
   int cpuinfo[4] = { 0, 0, 0, 0 };                  
   __cpuid( cpuinfo, 0 );          
   uint16_t hashe = 0;          
   uint16_t * ptr = (uint16_t *)(&cpuinfo[0]); 
   for ( uint32_t  i = 0; i < 8; i++ )   
      hashe += ptr[i];     

   return hashe;           
}        

const char* getMachineName()       
{        
   static char computerName[1024]; 
   DWORD size = 1024;     
   GetComputerName( computerName, &size );           
   return &(computerName[0]);      
}

std::string Int2String(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}
int String2Int(std::string String)
{
	int Integer;
	std::istringstream iss(String);
	iss >> Integer;
	return Integer;
}
int catchInt(std::string s) {

	int value = 0;
	for(int i=0;i<(int)s.size();i++){
		if(isdigit(s[i]))
			value += s[i];
	}
		
	return value;
}
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

string getHWID(){
			/*std::string result;
			result = Int2String(ma1+ma2)+Int2String(getCpuHash())+Int2String(getVolumeHash());

			return (String2Int(result));*/

	HKEY hKey = 0;
	wchar_t buf[255];
	DWORD dwBufSize = sizeof(buf);
	const wchar_t* subkey = L"Software\\Microsoft\\Cryptography";
	bool t = false;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subkey, 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExW(hKey, L"MachineGuid", 0, 0, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
		{
			t = true;
			RegCloseKey(hKey);
		}
		else
		{
			t = false;
		}
	}
	if (t) {
		wstring ws(buf);
		string str(ws.begin(), ws.end());
		return Int2String(203*getVolumeHash()) + str + Int2String(getVolumeHash()*9);
	}
	else
		return "";
}