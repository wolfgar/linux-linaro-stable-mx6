
imxdrm-objs := imx-drm-core.o
imxhdmi-objs := imx-hdmi.o dw-hdmi-audio.o

obj-$(CONFIG_DRM_IMX) += imxdrm.o

obj-$(CONFIG_DRM_IMX_PARALLEL_DISPLAY) += parallel-display.o
obj-$(CONFIG_DRM_IMX_TVE) += imx-tve.o
obj-$(CONFIG_DRM_IMX_LDB) += imx-ldb.o
obj-$(CONFIG_DRM_IMX_IPUV3_CORE) += ipu-v3/

imx-ipuv3-crtc-objs  := ipuv3-crtc.o ipuv3-plane.o
obj-$(CONFIG_DRM_IMX_IPUV3)	+= imx-ipuv3-crtc.o
obj-$(CONFIG_DRM_IMX_HDMI) += imxhdmi.o
obj-$(CONFIG_DRM_DW_HDMI_CEC) += dw-hdmi-cec.o
