#
# Copyright (C) 2010-2011 ARM Limited. All rights reserved.
# 
# This program is free software and is provided to you under the terms of the GNU General Public License version 2
# as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
# 
# A copy of the licence is included with the program, and can also be obtained from Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

# This file is called by the Linux build system.

# set up defaults if not defined by the user
TIMESTAMP ?= default
OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB = 64
USING_GPU_UTILIZATION = 0
PROFILING_SKIP_PP_JOBS ?= 0
PROFILING_SKIP_PP_AND_GP_JOBS ?= 0
MALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP ?= 0
MALI_PP_SCHEDULER_KEEP_SUB_JOB_STARTS_ALIGNED ?= 0
MALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP_BETWEEN_APPS ?= 0
MALI_UPPER_HALF_SCHEDULING ?= 1
MALI_ENABLE_CPU_CYCLES ?= 0

ifeq ($(USING_GPU_UTILIZATION), 1)
    ifeq ($(USING_DVFS), 1)
        $(error USING_GPU_UTILIZATION conflict with USING_DVFS you can read the Integration Guide to choose which one do you need)
    endif
endif

ifeq ($(CONFIG_MALI400_UMP),y)
	export EXTRA_DEFINES += -DCONFIG_MALI400_UMP=1
	ifeq ($(USE_UMPV2),1)
		UMP_SYMVERS_FILE ?= ../umpv2/Module.symvers
	else
		UMP_SYMVERS_FILE ?= ../ump/Module.symvers
	endif
	KBUILD_EXTRA_SYMBOLS = $(realpath $(UMP_SYMVERS_FILE))
	$(warning $(KBUILD_EXTRA_SYMBOLS))
endif

ifeq ($(CONFIG_MALI400_PROFILING),y)
ifeq ($(CONFIG_TRACEPOINTS),)
	$(warning CONFIG_TRACEPOINTS required for profiling)
else
	export EXTRA_DEFINES += -DCONFIG_MALI400_PROFILING=1
endif
endif

ifeq ($(CONFIG_MALI400_INTERNAL_PROFILING),y)
export EXTRA_DEFINES += -DCONFIG_MALI400_INTERNAL_PROFILING=1
endif

ifeq ($(CONFIG_MALI400_HEATMAPS_ENABLED),y)
export EXTRA_DEFINES += -DCONFIG_MALI400_HEATMAPS_ENABLED
endif

ifeq ($(CONFIG_MALI_DMA_BUF_MAP_ON_ATTACH),y)
export EXTRA_DEFINES += -DCONFIG_MALI_DMA_BUF_MAP_ON_ATTACH
endif

ifeq ($(CONFIG_MALI_SHARED_INTERRUPTS),y)
export EXTRA_DEFINES += -DCONFIG_MALI_SHARED_INTERRUPTS
endif

ifeq ($(CONFIG_MALI_DVFS),y)
export EXTRA_DEFINES += -DCONFIG_MALI_DVFS
endif

ifeq ($(CONFIG_MALI_PMU_PARALLEL_POWER_UP),y)
export EXTRA_DEFINES += -DCONFIG_MALI_PMU_PARALLEL_POWER_UP
endif

export EXTRA_DEFINES += -DCONFIG_MALI_DT

ifeq ($(CONFIG_MALI_PLATFORM_SC8830),y)
	MALI_PLATFORM := sc8830
	TARGET_PLATFORM := sc8830
endif

EXTRA_DEFINES += -DCONFIG_MALI400=1

mali-y += \
	linux/mali_osk_atomics.o \
	linux/mali_osk_irq.o \
	linux/mali_osk_wq.o \
	linux/mali_osk_locks.o \
	linux/mali_osk_wait_queue.o \
	linux/mali_osk_low_level_mem.o \
	linux/mali_osk_math.o \
	linux/mali_osk_memory.o \
	linux/mali_osk_misc.o \
	linux/mali_osk_mali.o \
	linux/mali_osk_notification.o \
	linux/mali_osk_time.o \
	linux/mali_osk_timers.o

mali-y += linux/mali_memory.o linux/mali_memory_os_alloc.o
mali-y += linux/mali_memory_external.o
mali-y += linux/mali_memory_block_alloc.o

mali-y += \
	linux/mali_ukk_mem.o \
	linux/mali_ukk_gp.o \
	linux/mali_ukk_pp.o \
	linux/mali_ukk_core.o \
	linux/mali_ukk_soft_job.o \
	linux/mali_ukk_timeline.o

# Source files which always are included in a build
mali-y += \
	common/mali_kernel_core.o \
	linux/mali_kernel_linux.o \
	common/mali_kernel_descriptor_mapping.o \
	common/mali_session.o \
	linux/mali_device_pause_resume.o \
	common/mali_kernel_vsync.o \
	linux/mali_ukk_vsync.o \
	linux/mali_kernel_sysfs.o \
	common/mali_mmu.o \
	common/mali_mmu_page_directory.o \
	common/mali_mem_validation.o \
	common/mali_hw_core.o \
	common/mali_gp.o \
	common/mali_pp.o \
	common/mali_pp_job.o \
	common/mali_gp_job.o \
	common/mali_soft_job.o \
	common/mali_scheduler.o \
	common/mali_executor.o \
	common/mali_group.o \
	common/mali_dlbu.o \
	common/mali_broadcast.o \
	common/mali_pm.o \
	common/mali_pmu.o \
	common/mali_user_settings_db.o \
	common/mali_kernel_utilization.o \
	common/mali_control_timer.o \
	common/mali_l2_cache.o \
	common/mali_timeline.o \
	common/mali_timeline_fence_wait.o \
	common/mali_timeline_sync_fence.o \
	common/mali_spinlock_reentrant.o \
	common/mali_pm_domain.o \
	linux/mali_osk_pm.o \
	linux/mali_pmu_power_up_down.o \
	__malidrv_build_info.o

mali-$(CONFIG_MALI400_PROFILING) += linux/mali_ukk_profiling.o
mali-$(CONFIG_MALI400_PROFILING) += linux/mali_osk_profiling.o

mali-$(CONFIG_MALI400_INTERNAL_PROFILING) += linux/mali_profiling_internal.o timestamp-$(TIMESTAMP)/mali_timestamp.o
ccflags-$(CONFIG_MALI400_INTERNAL_PROFILING) += -I$(src)/timestamp-$(TIMESTAMP)

mali-$(CONFIG_DMA_SHARED_BUFFER) += linux/mali_memory_dma_buf.o
mali-$(CONFIG_SYNC) += linux/mali_sync.o
ccflags-$(CONFIG_SYNC) += -Idrivers/staging/android

mali-$(CONFIG_MALI400_UMP) += linux/mali_memory_ump.o

mali-$(CONFIG_MALI_DVFS) += common/mali_dvfs_policy.o

# Tell the Linux build system from which .o file to create the kernel module
obj-$(CONFIG_MALI400) := mali.o

ccflags-y += $(EXTRA_DEFINES)

# Set up our defines, which will be passed to gcc
ccflags-y += -DSPRD_MEM_OPT_PAGE_TABLE_SHRINK
ccflags-y += -DSPRD_GPU_BOOST

ccflags-y += -DMALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP=$(MALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP)
ccflags-y += -DMALI_PP_SCHEDULER_KEEP_SUB_JOB_STARTS_ALIGNED=$(MALI_PP_SCHEDULER_KEEP_SUB_JOB_STARTS_ALIGNED)
ccflags-y += -DMALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP_BETWEEN_APPS=$(MALI_PP_SCHEDULER_FORCE_NO_JOB_OVERLAP_BETWEEN_APPS)
ccflags-y += -DMALI_STATE_TRACKING=1
ccflags-y += -DMALI_OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB=$(OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB)
ccflags-y += -DUSING_GPU_UTILIZATION=$(USING_GPU_UTILIZATION)
ccflags-y += -DMALI_ENABLE_CPU_CYCLES=$(MALI_ENABLE_CPU_CYCLES)

ifeq ($(MALI_UPPER_HALF_SCHEDULING),1)
	ccflags-y += -DMALI_UPPER_HALF_SCHEDULING
endif

ccflags-$(CONFIG_MALI400_UMP) += -I$(src)/../ump/include/ump
ccflags-$(CONFIG_MALI400_DEBUG) += -DDEBUG

# Use our defines when compiling
ccflags-y += -I$(src) -I$(src)/include -I$(src)/common -I$(src)/linux -I$(src)/linux/license/gpl -I$(src)/platform 

export EXTRA_DEFINES += -DMALI_FAKE_PLATFORM_DEVICE=1
export MALI_PLATFORM_FILES = $(wildcard platform/$(MALI_PLATFORM)/*.c)

ifneq ($(MALI_PLATFORM),)
mali-y += platform/$(MALI_PLATFORM)/mali_platform.o
ccflags-y += -I$(src)/platform/$(MALI_PLATFORM)
endif

# Get subversion revision number, fall back to only ${MALI_RELEASE_NAME} if no svn info is available
MALI_RELEASE_NAME=$(shell cat $(src)/.version 2> /dev/null)

#SVN_INFO = (cd $(src); svn info 2>/dev/null)

ifneq ($(shell $(SVN_INFO) 2>/dev/null),)
# SVN detected
SVN_REV := $(shell $(SVN_INFO) | grep '^Revision: '| sed -e 's/^Revision: //' 2>/dev/null)
DRIVER_REV := $(MALI_RELEASE_NAME)-r$(SVN_REV)
CHANGE_DATE := $(shell $(SVN_INFO) | grep '^Last Changed Date: ' | cut -d: -f2- | cut -b2-)
CHANGED_REVISION := $(shell $(SVN_INFO) | grep '^Last Changed Rev: ' | cut -d: -f2- | cut -b2-)
REPO_URL := $(shell $(SVN_INFO) | grep '^URL: ' | cut -d: -f2- | cut -b2-)

else # SVN
#GIT_REV := $(shell cd $(src); git describe --always 2>/dev/null)
ifneq ($(GIT_REV),)
# Git detected
DRIVER_REV := $(MALI_RELEASE_NAME)-$(GIT_REV)
CHANGE_DATE := $(shell cd $(src); git log -1 --format="%ci")
CHANGED_REVISION := $(GIT_REV)
REPO_URL := $(shell cd $(src); git describe --all --always 2>/dev/null)

else # Git
# No Git or SVN detected
DRIVER_REV := $(MALI_RELEASE_NAME)
CHANGE_DATE := $(MALI_RELEASE_NAME)
CHANGED_REVISION := $(MALI_RELEASE_NAME)
endif
endif

ccflags-y += -DSVN_REV_STRING=\"$(DRIVER_REV)\"
ccflags-y += -fno-PIC

VERSION_STRINGS :=
VERSION_STRINGS += API_VERSION=$(shell cd $(src); grep "\#define _MALI_API_VERSION" $(FILES_PREFIX)include/linux/mali/mali_utgard_uk_types.h | cut -d' ' -f 3 )
VERSION_STRINGS += REPO_URL=$(REPO_URL)
VERSION_STRINGS += REVISION=$(DRIVER_REV)
VERSION_STRINGS += CHANGED_REVISION=$(CHANGED_REVISION)
VERSION_STRINGS += CHANGE_DATE=$(CHANGE_DATE)
#VERSION_STRINGS += BUILD_DATE=$(shell date)
ifdef CONFIG_MALI400_DEBUG
VERSION_STRINGS += BUILD=debug
else
VERSION_STRINGS += BUILD=release
endif
VERSION_STRINGS += TARGET_PLATFORM=$(TARGET_PLATFORM)
VERSION_STRINGS += MALI_PLATFORM=$(MALI_PLATFORM)
VERSION_STRINGS += KDIR=$(KDIR)
VERSION_STRINGS += OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB=$(OS_MEMORY_KERNEL_BUFFER_SIZE_IN_MB)
VERSION_STRINGS += USING_UMP=$(CONFIG_MALI400_UMP)
VERSION_STRINGS += USING_PROFILING=$(CONFIG_MALI400_PROFILING)
VERSION_STRINGS += USING_INTERNAL_PROFILING=$(CONFIG_MALI400_INTERNAL_PROFILING)
VERSION_STRINGS += USING_GPU_UTILIZATION=$(USING_GPU_UTILIZATION)
VERSION_STRINGS += USING_DVFS=$(CONFIG_MALI_DVFS)
VERSION_STRINGS += MALI_UPPER_HALF_SCHEDULING=$(MALI_UPPER_HALF_SCHEDULING)

# Create file with Mali driver configuration
$(src)/__malidrv_build_info.c:
	@echo 'const char *__malidrv_build_info(void) { return "malidrv: $(VERSION_STRINGS)";}' > $(src)/__malidrv_build_info.c
