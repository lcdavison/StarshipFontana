#include "SFAsset.h"

SFAsset::SFAsset(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : type(type), sf_window(window), name(name) {
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

void SFAsset::SetupSprite(const std::string path) {
	sprite = IMG_LoadTexture(sf_window->getRenderer(), path.c_str());

	if(!sprite) { 
		printf("Failed to load sprite");
		return;
	}

	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w, h);
}

void SFAsset::SetupSpriteSheet(const std::string path, const int number_of_sprites) {
	SDL_Rect sprites[number_of_sprites];


}

void SFAsset::SetAlpha(const int value) { SDL_SetTextureAlphaMod(sprite, value); } 

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

bool SFAsset::IsOutsideWindow() {
	return bbox->GetY() < 0 || bbox->GetY() > sf_window->GetHeight() || bbox->GetX() + bbox->GetWidth() < 0 || bbox->GetX() > sf_window->GetWidth();
}

std::string SFAsset::GetName() const { return name; }

SFASSETTYPE SFAsset::GetType() const { return type; }

void SFAsset::OnUpdate() {}                         

void SFAsset::OnRender() {
	// 1. Get the SDL_Rect from SFBoundingBox
	SDL_Rect rect = bbox->GetBox();

	// 2. Blit the sprite onto the level
	SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
	Vector2 v = Vector2(-5.0f, 0) * movement_speed;
	if(GetPosition().getX() >= 0)	bbox->Translate(v);
}

void SFAsset::GoEast() {
	Vector2 v = Vector2(5.0f, 0) * movement_speed;

	//	Check that the asset is left of window width
	if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth())	bbox->Translate(v);
}

void SFAsset::GoNorth() {
	Vector2 v = Vector2(0.0f, -5.0f) * movement_speed;
	bbox->Translate(v);
}

void SFAsset::GoSouth() {
	Vector2 v = Vector2(0.0f, 5.0f) * movement_speed;
	bbox->Translate(v);
}

float SFAsset::DistanceTo(std::shared_ptr<SFAsset> other) {
	return GetPosition().DistanceTo(other->GetPosition());
}

void SFAsset::MoveTowards(const std::shared_ptr<SFAsset> other) {

	Vector2 direction = (GetPosition() - other->GetCenter()).normalize();
	direction = direction * movement_speed;

	if(GetPosition() != other->GetCenter()) bbox->Translate(direction);
}

void SFAsset::Lerp(const std::shared_ptr<SFAsset> other, float time) {

	Vector2 direction = (GetPosition() - other->GetPosition());
	direction = direction * movement_speed * time;

	if(GetPosition() != other->GetCenter()) bbox->Translate(direction);
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
	return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
	return bbox;
}

void SFAsset::SetNotAlive() {
	alive = false;
}

bool SFAsset::IsAlive() {
	return alive;
}

void SFAsset::HandleCollision() {
	if (SFASSET_PROJECTILE == type || SFASSET_ALIEN == type) {
		SetNotAlive();
	}
}
