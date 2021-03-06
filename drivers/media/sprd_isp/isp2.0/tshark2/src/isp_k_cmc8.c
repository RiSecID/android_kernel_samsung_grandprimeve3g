/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <linux/uaccess.h>
#include <linux/sprd_mm.h>
#include <video/sprd_isp.h>
#include "isp_reg.h"

static int32_t isp_k_cmc8_block(struct isp_io_param *param)
{
	int32_t ret = 0;
	uint32_t val = 0;
	struct isp_dev_cmc8_info_v1 cmc8_info;

	memset(&cmc8_info, 0x00, sizeof(cmc8_info));

	ret = copy_from_user((void *)&cmc8_info, param->property_param, sizeof(cmc8_info));
	if (0 != ret) {
		printk("isp_k_cmc8_block: copy error, ret=0x%x\n", (uint32_t)ret);
		return -1;
	}

	REG_MWR(ISP_CMC8_PARAM, BIT_0, cmc8_info.bypass);

	REG_MWR(ISP_CMC8_PARAM, BIT_3, cmc8_info.buf_sel << 3);

	REG_MWR(ISP_CMC8_PARAM, 0x3FF << 4, cmc8_info.alpha << 4);

	REG_MWR(ISP_CMC8_PARAM, BIT_1, cmc8_info.alpha_bypass << 1);

	val = ((cmc8_info.matrix.val[1] & 0x3FFF) << 14) | (cmc8_info.matrix.val[0] & 0x3FFF);
	REG_WR(ISP_CMC8_MATRIX0, val);
	val = ((cmc8_info.matrix.val[3] & 0x3FFF) << 14) | (cmc8_info.matrix.val[2] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0 + 4), val);
	val = ((cmc8_info.matrix.val[5] & 0x3FFF) << 14) | (cmc8_info.matrix.val[4] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0 + 8), val);
	val = ((cmc8_info.matrix.val[7] & 0x3FFF) << 14) | (cmc8_info.matrix.val[6] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0 + 12), val);
	val = cmc8_info.matrix.val[8] & 0x3FFF;
	REG_WR((ISP_CMC8_MATRIX0 + 16), val);

	val = ((cmc8_info.matrix_buf.val[1] & 0x3FFF) << 14) | (cmc8_info.matrix_buf.val[0] & 0x3FFF);
	REG_WR(ISP_CMC8_MATRIX0_BUF, val);
	val = ((cmc8_info.matrix_buf.val[3] & 0x3FFF) << 14) | (cmc8_info.matrix_buf.val[2] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0_BUF + 4), val);
	val = ((cmc8_info.matrix_buf.val[5] & 0x3FFF) << 14) | (cmc8_info.matrix_buf.val[4] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0_BUF + 8), val);
	val = ((cmc8_info.matrix_buf.val[7] & 0x3FFF) << 14) | (cmc8_info.matrix_buf.val[6] & 0x3FFF);
	REG_WR((ISP_CMC8_MATRIX0_BUF + 12), val);
	val = cmc8_info.matrix_buf.val[8] & 0x3FFF;
	REG_WR((ISP_CMC8_MATRIX0_BUF + 16), val);

	return ret;
}

int32_t isp_k_cfg_cmc8(struct isp_io_param *param)
{
	int32_t ret = 0;

	if (!param) {
		printk("isp_k_cfg_cmc: param is null error.\n");
		return -1;
	}

	if (NULL == param->property_param) {
		printk("isp_k_cfg_cmc: property_param is null error.\n");
		return -1;
	}

	switch(param->property) {
	case ISP_PRO_CMC8_BLOCK:
		ret = isp_k_cmc8_block(param);
		break;
	default:
		printk("isp_k_cfg_cmc: fail cmd id:%d, not supported.\n", param->property);
		break;
	}

	return ret;
}

