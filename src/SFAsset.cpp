#include "SFAsset.h"

SFAsset::SFAsset(SFASSETTYPE type, std::shared_ptr<SFWindow> window) : type(type), sf_window(window) {
}

SFAsset::SFAsset(const SFAsset& a) {
		sprite = a.sprite;
		sf_window = a.sf_window;
		bbox = a.bbox;
		type = a.type;
}

SFAsset::~SFAsset() {
		bbox.reset();
		if (sprite) {
				SDL_DestroyTexture(sprite);
				sprite = nullptr;
		}
}

void SFAsset::SetupSprite(){}

void SFAsset::Update() {

}

void SFAsset::SetPosition(Point2 & point) {
		Vector2 v(point.getX(), point.getY());
		bbox->SetPosition(point);
}

Point2 SFAsset::GetPosition() {
		return Point2(bbox->GetX(), bbox->GetY());
}

Point2 SFAsset::GetCenter() {
		return Point2(bbox->GetX() + bbox->GetWidth() / 2, bbox->GetY() + bbox->GetHeight() / 2);
}

void SFAsset::OnRender() {
		// 1. Get the SDL_Rect from SFBoundingBox
		SDL_Rect rect = bbox->GetBox();

		// 2. Blit the sprite onto the level
		SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
		Vector2 v = Vector2(-5.0f, 0);
		if(GetPosition().getX() >= 0)	bbox->Translate(v);
}

void SFAsset::GoEast() {
		Vector2 v = Vector2(5.0f, 0);

		//	Check that the ship is left of window width
		if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth())	bbox->Translate(v);
}

void SFAsset::GoNorth() {
		Vector2 v = Vector2(0.0f, -5.0f);
		bbox->Translate(v);
}

void SFAsset::GoSouth() {
		Vector2 v = Vector2(0.0f, 5.0f);
		bbox->Translate(v);
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
		return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
		return bbox;
}

void SFAsset::SetNotAlive() {
		type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
		return (SFASSET_DEAD != type);
}

void SFAsset::HandleCollision() {
		if (SFASSET_PROJECTILE == type || SFASSET_ALIEN == type) {
				SetNotAlive();
		}
}
