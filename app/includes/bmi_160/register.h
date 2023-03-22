
/* registers */
#define BMI160_REG_CHIPID		0x00
#define BMI160_REG_ERR			0x02
#define BMI160_REG_PMU_STATUS		0x03
#define BMI160_REG_DATA_MAG_X		0x04
#define BMI160_REG_DATA_MAG_Y		0x06
#define BMI160_REG_DATA_MAG_Z		0x08
#define BMI160_REG_DATA_RHALL		0x0A
#define BMI160_REG_DATA_GYR_X		0x0C
#define BMI160_REG_DATA_GYR_Y		0x0E
#define BMI160_REG_DATA_GYR_Z		0x10
#define BMI160_REG_DATA_ACC_X		0x12
#define BMI160_REG_DATA_ACC_Y		0x14
#define BMI160_REG_DATA_ACC_Z		0x16
#define BMI160_REG_SENSORTIME0		0x18
#define BMI160_REG_SENSORTIME1		0x19
#define BMI160_REG_SENSORTIME2		0x1A
#define BMI160_REG_STATUS		0x1B
#define BMI160_REG_INT_STATUS0		0x1C
#define BMI160_REG_INT_STATUS1		0x1D
#define BMI160_REG_INT_STATUS2		0x1E
#define BMI160_REG_INT_STATUS3		0x1F
#define BMI160_REG_TEMPERATURE0		0x20
#define BMI160_REG_TEMPERATURE1		0x21
#define BMI160_REG_FIFO_LENGTH0		0x22
#define BMI160_REG_FIFO_LENGTH1		0x23
#define BMI160_REG_FIFO_DATA		0x24
#define BMI160_REG_ACC_CONF		0x40
#define BMI160_REG_ACC_RANGE		0x41
#define BMI160_REG_GYR_CONF		0x42
#define BMI160_REG_GYR_RANGE		0x43
#define BMI160_REG_MAG_CONF		0x44
#define BMI160_REG_FIFO_DOWNS		0x45
#define BMI160_REG_FIFO_CONFIG0		0x46
#define BMI160_REG_FIFO_CONFIG1		0x47
#define BMI160_REG_MAG_IF0		0x4B
#define BMI160_REG_MAG_IF1		0x4C
#define BMI160_REG_MAG_IF2		0x4D
#define BMI160_REG_MAG_IF3		0x4E
#define BMI160_REG_MAG_IF4		0x4F
#define BMI160_REG_INT_EN0		0x50
#define BMI160_REG_INT_EN1		0x51
#define BMI160_REG_INT_EN2		0x52
#define BMI160_REG_INT_OUT_CTRL		0x53
#define BMI160_REG_INT_LATCH		0x54
#define BMI160_REG_INT_MAP0		0x55
#define BMI160_REG_INT_MAP1		0x56
#define BMI160_REG_INT_MAP2		0x57
#define BMI160_REG_INT_DATA0		0x58
#define BMI160_REG_INT_DATA1		0x59
#define BMI160_REG_INT_LOWHIGH0		0x5A
#define BMI160_REG_INT_LOWHIGH1		0x5B
#define BMI160_REG_INT_LOWHIGH2		0x5C
#define BMI160_REG_INT_LOWHIGH3		0x5D
#define BMI160_REG_INT_LOWHIGH4		0x5E
#define BMI160_REG_INT_MOTION0		0x5F
#define BMI160_REG_INT_MOTION1		0x60
#define BMI160_REG_INT_MOTION2		0x61
#define BMI160_REG_INT_MOTION3		0x62
#define BMI160_REG_INT_TAP0		0x63
#define BMI160_REG_INT_TAP1		0x64
#define BMI160_REG_INT_ORIENT0		0x65
#define BMI160_REG_INT_ORIENT1		0x66
#define BMI160_REG_INT_FLAT0		0x67
#define BMI160_REG_INT_FLAT1		0x68
#define BMI160_REG_FOC_CONF		0x69
#define BMI160_REG_CONF			0x6A
#define BMI160_REG_IF_CONF		0x6B
#define BMI160_REG_PMU_TRIGGER		0x6C
#define BMI160_REG_SELF_TEST		0x6D
#define BMI160_REG_NV_CONF		0x70
#define BMI160_REG_OFFSET_ACC_X		0x71
#define BMI160_REG_OFFSET_ACC_Y		0x72
#define BMI160_REG_OFFSET_ACC_Z		0x73
#define BMI160_REG_OFFSET_GYR_X		0x74
#define BMI160_REG_OFFSET_GYR_Y		0x75
#define BMI160_REG_OFFSET_GYR_Z		0x76
#define BMI160_REG_OFFSET_EN		0x77
#define BMI160_REG_STEP_CNT0		0x78
#define BMI160_REG_STEP_CNT1		0x79
#define BMI160_REG_STEP_CONF0		0x7A
#define BMI160_REG_STEP_CONF1		0x7B
#define BMI160_REG_CMD			0x7E

/* This is not a real register; reading it activates SPI on the BMI160 */
#define BMI160_SPI_START		0x7F

#define BMI160_REG_COUNT		0x80

/* Indicates a read operation; bit 7 is clear on write s*/
#define BMI160_REG_READ			BIT(7)
#define BMI160_REG_MASK			0x7f

/* bitfields */

/* BMI160_REG_ERR */
#define BMI160_ERR_FATAL		BIT(0)
#define BMI160_ERR_CODE			BIT(1)
#define BMI160_ERR_CODE_MASK		(0xf << 1)
#define BMI160_ERR_I2C_FAIL		BIT(5)
#define BMI160_ERR_DROP_CMD		BIT(6)
#define BMI160_ERR_MAG_DRDY		BIT(7)

/* BMI160_REG_PMU_STATUS */
#define BMI160_PMU_STATUS_MAG_MASK	0x3
#define BMI160_PMU_STATUS_MAG_POS	0
#define BMI160_PMU_STATUS_GYR_POS	2
#define BMI160_PMU_STATUS_GYR_MASK	(0x3 << 2)
#define BMI160_PMU_STATUS_ACC_POS	4
#define BMI160_PMU_STATUS_ACC_MASK	(0x3 << 4)

#define BMI160_PMU_SUSPEND		0
#define BMI160_PMU_NORMAL		1
#define BMI160_PMU_LOW_POWER		2
#define BMI160_PMU_FAST_START		3

/* BMI160_REG_STATUS */
#define BMI160_STATUS_GYR_SELFTEST	BIT(1)
#define BMI160_STATUS_MAG_MAN_OP	BIT(2)
#define BMI160_STATUS_FOC_RDY		BIT(3)
#define BMI160_STATUS_NVM_RDY		BIT(4)
#define BMI160_STATUS_MAG_DRDY		BIT(5)
#define BMI160_STATUS_GYR_DRDY		BIT(6)
#define BMI160_STATUS_ACC_DRDY		BIT(7)

/* BMI160_REG_INT_STATUS0 */
#define BMI160_INT_STATUS0_STEP		BIT(0)
#define BMI160_INT_STATUS0_SIGMOT	BIT(1)
#define BMI160_INT_STATUS0_ANYM		BIT(2)
#define BMI160_INT_STATUS0_PMU_TRIG	BIT(3)
#define BMI160_INT_STATUS0_D_TAP	BIT(4)
#define BMI160_INT_STATUS0_S_TAP	BIT(5)
#define BMI160_INT_STATUS0_ORIENT	BIT(6)
#define BMI160_INT_STATUS0_FLAT		BIT(7)

/* BMI160_REG_INT_STATUS1 */
#define BMI160_INT_STATUS1_HIGHG	BIT(2)
#define BMI160_INT_STATUS1_LOWG		BIT(3)
#define BMI160_INT_STATUS1_DRDY		BIT(4)
#define BMI160_INT_STATUS1_FFULL	BIT(5)
#define BMI160_INT_STATUS1_FWM		BIT(6)
#define BMI160_INT_STATUS1_NOMO		BIT(7)

/* BMI160_REG_INT_STATUS2 */
#define BMI160_INT_STATUS2_ANYM_FIRST_X BIT(0)
#define BMI160_INT_STATUS2_ANYM_FIRST_Y BIT(1)
#define BMI160_INT_STATUS2_ANYM_FIRST_Z BIT(2)
#define BMI160_INT_STATUS2_ANYM_SIGN	BIT(3)
#define BMI160_INT_STATUS2_TAP_FIRST_X	BIT(4)
#define BMI160_INT_STATUS2_TAP_FIRST_Y	BIT(5)
#define BMI160_INT_STATUS2_TAP_FIRST_Z	BIT(6)
#define BMI160_INT_STATUS2_TAP_SIGN	BIT(7)

/* BMI160_REG_INT_STATUS3 */
#define BMI160_INT_STATUS3_HIGH_FIRST_X BIT(0)
#define BMI160_INT_STATUS3_HIGH_FIRST_Y BIT(1)
#define BMI160_INT_STATUS3_HIGH_FIRST_Z BIT(2)
#define BMI160_INT_STATUS3_HIGH_SIGN	BIT(3)
#define BMI160_INT_STATUS3_ORIENT_1_0	BIT(4)
#define BMI160_INT_STATUS3_ORIENT_2	BIT(6)
#define BMI160_INT_STATUS3_FLAT		BIT(7)

/* BMI160_REG_ACC_CONF */
#define BMI160_ACC_CONF_ODR_POS		0
#define BMI160_ACC_CONF_ODR_MASK	0xF
#define BMI160_ACC_CONF_BWP_POS		4
#define BMI160_ACC_CONF_BWP_MASK	(0x7 << 4)
#define BMI160_ACC_CONF_US_POS		7
#define BMI160_ACC_CONF_US_MASK		BIT(7)

/* BMI160_REG_GYRO_CONF */
#define BMI160_GYR_CONF_ODR_POS	0
#define BMI160_GYR_CONF_ODR_MASK	0xF
#define BMI160_GYR_CONF_BWP_POS	4
#define BMI160_GYR_CONF_BWP_MASK	(0x3 << 4)

/* BMI160_REG_OFFSET_EN */
#define BMI160_GYR_OFS_EN_POS		7
#define BMI160_ACC_OFS_EN_POS		6
#define BMI160_GYR_MSB_OFS_Z_POS	4
#define BMI160_GYR_MSB_OFS_Z_MASK	(BIT(4) | BIT(5))
#define BMI160_GYR_MSB_OFS_Y_POS	2
#define BMI160_GYR_MSB_OFS_Y_MASK	(BIT(2) | BIT(3))
#define BMI160_GYR_MSB_OFS_X_POS	0
#define BMI160_GYR_MSB_OFS_X_MASK	(BIT(0) | BIT(1))

/* BMI160_REG_CMD */
#define BMI160_CMD_START_FOC		3
#define BMI160_CMD_PMU_ACC		0x10
#define BMI160_CMD_PMU_GYR		0x14
#define BMI160_CMD_PMU_MAG		0x18
#define BMI160_CMD_SOFT_RESET		0xB6

#define BMI160_CMD_PMU_BIT		0x10
#define BMI160_CMD_PMU_MASK		0x0c
#define BMI160_CMD_PMU_SHIFT		2
#define BMI160_CMD_PMU_VAL_MASK		0x3

/* BMI160_REG_FOC_CONF */
#define BMI160_FOC_ACC_Z_POS		0
#define BMI160_FOC_ACC_Y_POS		2
#define BMI160_FOC_ACC_X_POS		4
#define BMI160_FOC_GYR_EN_POS		6

/* BMI160_REG_INT_MOTION0 */
#define BMI160_ANYM_DUR_POS		0
#define BMI160_ANYM_DUR_MASK		0x3

/* BMI160_REG_INT_EN0 */
#define BMI160_INT_FLAT_EN		BIT(7)
#define BMI160_INT_ORIENT_EN		BIT(6)
#define BMI160_INT_S_TAP_EN		BIT(5)
#define BMI160_INT_D_TAP_EN		BIT(4)
#define BMI160_INT_ANYM_Z_EN		BIT(2)
#define BMI160_INT_ANYM_Y_EN		BIT(1)
#define BMI160_INT_ANYM_X_EN		BIT(0)
#define BMI160_INT_ANYM_MASK		(BIT(0) | BIT(1) | BIT(2))

/* BMI160_REG_INT_EN1 */
#define BMI160_INT_FWM_EN		BIT(6)
#define BMI160_INT_FFULL_EN		BIT(5)
#define BMI160_INT_DRDY_EN		BIT(4)
#define BMI160_INT_LOWG_EN		BIT(3)
#define BMI160_INT_HIGHG_Z_EN		BIT(2)
#define BMI160_INT_HIGHG_Y_EN		BIT(1)
#define BMI160_INT_HIGHG_X_EN		BIT(0)
#define BMI160_INT_HIGHG_MASK		(BIT(0) | BIT(1) | BIT(2))

/* BMI160_REG_INT_EN2 */
#define BMI160_INT_STEP_DET_EN		BIT(3)
#define BMI160_INT_STEP_NOMO_Z_EN	BIT(2)
#define BMI160_INT_STEP_NOMO_Y_EN	BIT(1)
#define BMI160_INT_STEP_NOMO_X_EN	BIT(0)
#define BMI160_INT_STEP_NOMO_MASK	(BIT(0) | BIT(1) | BIT(2))

/* BMI160_REG_INT_OUT_CTRL */
#define BMI160_INT2_OUT_EN		BIT(7)
#define BMI160_INT2_OD			BIT(6)
#define BMI160_INT2_LVL			BIT(5)
#define BMI160_INT2_EDGE_CTRL		BIT(4)
#define BMI160_INT1_OUT_EN		BIT(3)
#define BMI160_INT1_OD			BIT(2)
#define BMI160_INT1_LVL			BIT(1)
#define BMI160_INT1_EDGE_CTRL		BIT(0)

/* other */
#define BMI160_CHIP_ID			0xD1
#define BMI160_TEMP_OFFSET		23
