 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Autoconfig device support
  *
  * (c) 1996 Ed Hanway
  */

#ifndef UAE_AUTOCONF_H
#define UAE_AUTOCONF_H

#include "uae/types.h"
#ifdef FSUAE
#include "uae/memory.h"
#include "uae/limits.h"
#endif
#include "traps.h"

#define AFTERDOS_INIT_PRI ((-121) & 0xff)
#define AFTERDOS_PRI ((-122) & 0xff)

#define RTAREA_DEFAULT 0xf00000
#define RTAREA_BACKUP  0xef0000
#define RTAREA_BACKUP_2 0xdb0000
#define RTAREA_SIZE 0x10000

#define RTAREA_TRAPS 0x3000
#define RTAREA_RTG 0x3800
#define RTAREA_TRAMPOLINE 0x3a00
#define RTAREA_DATAREGION 0xF000

#define RTAREA_FSBOARD 0xFFEC
#define RTAREA_HEARTBEAT 0xFFF0
#define RTAREA_TRAPTASK 0xFFF4
#define RTAREA_EXTERTASK 0xFFF8
#define RTAREA_INTREQ 0xFFFC

#define RTAREA_TRAP_DATA 0x4000
#define RTAREA_TRAP_DATA_SIZE 0x8000
#define RTAREA_TRAP_DATA_SLOT_SIZE 0x2000 // 8192
#define RTAREA_TRAP_DATA_SECOND 80
#define RTAREA_TRAP_DATA_TASKWAIT (RTAREA_TRAP_DATA_SECOND - 4)
#define RTAREA_TRAP_DATA_EXTRA 144
#define RTAREA_TRAP_DATA_EXTRA_SIZE (RTAREA_TRAP_DATA_SLOT_SIZE - RTAREA_TRAP_DATA_EXTRA)

#define RTAREA_TRAP_STATUS 0xF000
#define RTAREA_TRAP_STATUS_SIZE 8
#define RTAREA_TRAP_STATUS_SECOND 4

#define RTAREA_VARIABLES 0x3F00
#define RTAREA_VARIABLES_SIZE 0x100
#define RTAREA_SYSBASE 0x3FFC
#define RTAREA_GFXBASE 0x3FF8
#define RTAREA_INTBASE 0x3FF4
#define RTAREA_INTXY 0x3FF0

#define RTAREA_TRAP_DATA_NUM (RTAREA_TRAP_DATA_SIZE / RTAREA_TRAP_DATA_SLOT_SIZE)
#define RTAREA_TRAP_DATA_SEND_NUM 1

#define RTAREA_TRAP_SEND_STATUS (RTAREA_TRAP_STATUS + RTAREA_TRAP_STATUS_SIZE * RTAREA_TRAP_DATA_NUM)
#define RTAREA_TRAP_SEND_DATA (RTAREA_TRAP_DATA + RTAREA_TRAP_DATA_SLOT_SIZE * RTAREA_TRAP_DATA_NUM)

#define UAEBOARD_DATAREGION_START 0x4000
#define UAEBOARD_DATAREGION_SIZE 0xc000

extern uae_u32 addr (int);
extern void db (uae_u8);
extern void dw (uae_u16);
extern void dl (uae_u32);
extern uae_u32 ds_ansi (const uae_char*);
extern uae_u32 ds (const TCHAR*);
extern uae_u32 ds_bstr_ansi (const uae_char*);
extern uae_u8 dbg (uaecptr);
extern void calltrap (uae_u32);
extern void org (uae_u32);
extern uae_u32 here (void);
extern uaecptr makedatatable (uaecptr resid, uaecptr resname, uae_u8 type, uae_s8 priority, uae_u16 ver, uae_u16 rev);
extern uae_u32 boot_rom_copy(TrapContext*, uaecptr, int);
extern void add_rom_absolute(uaecptr addr);
extern void save_rom_absolute(uaecptr addr);

extern void align (int);

extern volatile uae_atomic uae_int_requested;
extern void rtarea_reset(void);
extern bool rethink_traps(void);

#define RTS 0x4e75
#define RTE 0x4e73

extern uaecptr EXPANSION_explibname, EXPANSION_doslibname, EXPANSION_uaeversion;
extern uaecptr EXPANSION_explibbase, EXPANSION_uaedevname, EXPANSION_haveV36;
extern uaecptr EXPANSION_bootcode, EXPANSION_nullfunc;

extern uaecptr ROM_filesys_resname, ROM_filesys_resid;
extern uaecptr ROM_filesys_diagentry;
extern uaecptr ROM_hardfile_resname, ROM_hardfile_resid;
extern uaecptr ROM_hardfile_init;
extern uaecptr filesys_initcode, filesys_initcode_ptr;

extern int is_hardfile(int unit_no);
extern int nr_units(void);
extern int nr_directory_units(struct uae_prefs*);
extern uaecptr need_uae_boot_rom(struct uae_prefs*);

struct mountedinfo
{
    uae_s64 size;
    bool ismounted;
    bool ismedia;
	int error;
    int nrcyls;
	TCHAR rootdir[MAX_DPATH];
};

extern int get_filesys_unitconfig (struct uae_prefs *p, int index, struct mountedinfo*);
extern int kill_filesys_unitconfig (struct uae_prefs *p, int nr);
extern int move_filesys_unitconfig (struct uae_prefs *p, int nr, int to);
extern TCHAR *validatedevicename (TCHAR *s, const TCHAR *def);
extern TCHAR *validatevolumename (TCHAR *s, const TCHAR *def);

int filesys_insert (int nr, const TCHAR *volume, const TCHAR *rootdir, bool readonly, int flags);
int filesys_eject (int nr);
int filesys_media_change (const TCHAR *rootdir, int inserted, struct uaedev_config_data *uci);

extern TCHAR *filesys_createvolname (const TCHAR *volname, const TCHAR *rootdir, struct zvolume *zv, const TCHAR *def);
extern int target_get_volume_name (struct uaedev_mount_info *mtinf, struct uaedev_config_info *ci, bool inserted, bool fullcheck, int cnt);

extern int sprintf_filesys_unit (TCHAR *buffer, int num);

extern void filesys_reset (void);
extern void filesys_cleanup (void);
extern void filesys_prepare_reset (void);
extern void filesys_start_threads (void);
extern void filesys_flush_cache (void);
extern void filesys_free_handles (void);
extern void filesys_vsync (void);
#ifdef FSUAE
extern void filesys_hsync (void);
#endif

extern void filesys_install (void);
extern void filesys_install_code (void);
extern uaecptr filesys_get_entry(int);
extern void filesys_store_devinfo (uae_u8 *);
extern void hardfile_install (void);
extern void hardfile_reset (void);
extern void emulib_install (void);
extern uae_u32 uaeboard_demux (uae_u32*);
extern void expansion_init (void);
extern void expansion_cleanup (void);
extern void expansion_clear (void);
extern uaecptr expansion_startaddress(struct uae_prefs*, uaecptr addr, uae_u32 size);
extern bool expansion_is_next_board_fastram(void);
extern uaecptr uaeboard_alloc_ram(uae_u32);
extern uae_u8 *uaeboard_map_ram(uaecptr);
extern void expansion_scan_autoconfig(struct uae_prefs*, bool);
extern void expansion_generate_autoconfig_info(struct uae_prefs *p);
extern struct autoconfig_info *expansion_get_autoconfig_info(struct uae_prefs*, int romtype, int devnum);
extern struct autoconfig_info *expansion_get_autoconfig_data(struct uae_prefs *p, int index);
extern struct autoconfig_info *expansion_get_autoconfig_by_address(struct uae_prefs *p, uaecptr addr);
extern void expansion_set_autoconfig_sort(struct uae_prefs *p);
extern int expansion_autoconfig_move(struct uae_prefs *p, int index, int direction);
extern bool alloc_expansion_bank(addrbank *bank, struct autoconfig_info *aci);
extern void free_expansion_bank(addrbank *bank);

extern void uaegfx_install_code (uaecptr);

extern uae_u32 emulib_target_getcpurate (uae_u32, uae_u32*);

typedef bool (*DEVICE_INIT)(struct autoconfig_info*);
typedef void(*DEVICE_ADD)(int, struct uaedev_config_info*, struct romconfig*);
typedef bool(*E8ACCESS)(int, uae_u32*, int, bool);
typedef void(*DEVICE_MEMORY_CALLBACK)(struct romconfig*, uae_u8*, int);
#define EXPANSIONTYPE_SCSI 1
#define EXPANSIONTYPE_IDE 2
#define EXPANSIONTYPE_24BIT 4
#define EXPANSIONTYPE_IDE_PORT_DOUBLED 8
#define EXPANSIONTYPE_SASI 16
#define EXPANSIONTYPE_CUSTOM 32
#define EXPANSIONTYPE_PCI_BRIDGE 64
#define EXPANSIONTYPE_PARALLEL_ADAPTER 128
#define EXPANSIONTYPE_X86_BRIDGE 256
#define EXPANSIONTYPE_CUSTOM_SECONDARY 512
#define EXPANSIONTYPE_RTG 1024
#define EXPANSIONTYPE_SOUND 2048
#define EXPANSIONTYPE_FLOPPY 4096
#define EXPANSIONTYPE_NET 8192
#define EXPANSIONTYPE_INTERNAL 16384
struct expansionboardsettings
{
	const TCHAR *name;
	const TCHAR *configname;
	bool multiselect;
	bool invert;
	int bitshift;
};
struct expansionsubromtype
{
	const TCHAR *name;
	const TCHAR *configname;
	uae_u32 romtype;
	int memory_mid, memory_pid;
	uae_u32 memory_serial;
	bool memory_after;
	uae_u8 autoconfig[16];
};
struct expansionromtype
{
	const TCHAR *name;
	const TCHAR *friendlyname;
	const TCHAR *friendlymanufacturer;
	DEVICE_INIT init, init2;
	DEVICE_ADD add;
	uae_u32 romtype;
	uae_u32 romtype_extra;
	uae_u32 parentromtype;
	int zorro;
	bool singleonly;
	const struct expansionsubromtype *subtypes;
	int defaultsubtype;
	bool autoboot_jumper;
	int deviceflags;
	int memory_mid, memory_pid;
	uae_u32 memory_serial;
	bool memory_after;
	DEVICE_MEMORY_CALLBACK memory_callback;
	bool id_jumper;
	const struct expansionboardsettings *settings;
	uae_u8 autoconfig[16];
};
extern const struct expansionromtype expansionroms[];
struct cpuboardsubtype
{
	const TCHAR *name;
	const TCHAR *configname;
	int romtype, romtype_extra;
	DEVICE_ADD add;
	int deviceflags;
	int memorytype;
	int maxmemory;
	int z3extra;
	DEVICE_INIT init, init2;
	int initzorro;
	int initflag;
	const struct expansionboardsettings *settings;
	E8ACCESS e8;
	// if includes Z2 or Z3 RAM
	int memory_mid, memory_pid;
	uae_u32 memory_serial;
	bool memory_after;
	uae_u8 autoconfig[16];
};
struct cpuboardtype
{
	int id;
	const TCHAR *name;
	const struct cpuboardsubtype *subtypes;
	int defaultsubtype;
};
extern const struct cpuboardtype cpuboards[];

#endif /* UAE_AUTOCONF_H */
