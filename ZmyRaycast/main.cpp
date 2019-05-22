#include "World.h"

int main(void) {
	// 世界类
	World w;

	// 构建场景
	w.build();

	// 绘制场景
	w.render_scene();

	return(0);
}