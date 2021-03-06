#include "pch.h"
#include "CppUnitTest.h"
#include <Bomb.h>
#include <BombManager.h>
#include <Square.h>
#include <Map.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef unsigned int uint;
namespace UTests
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TEST_METHOD1)
        {
			auto b = std::make_unique<Bomb>(-1.0f, 1.0f, 1.0f, -1.0f);
			
			Assert::IsFalse(b->isActive());
			b->setActive();
			Assert::IsTrue(b->isActive());
			b->disActive();
			Assert::IsFalse(b->isActive());

			b->setExplosionTime(2.0f);
			Assert::AreEqual(2.0f, b->getExplosionTime());
			b->setActive();
			Assert::IsFalse(b->updateTime(0.1f));

			Assert::IsTrue(b->updateTime(1.91f));
			Assert::IsFalse(b->isActive());
        }
		TEST_METHOD(TEST_METHOD2)
		{
			auto manager = std::make_unique<BombManager>(
				Vertex2f{ static_cast<float>(400) / 2.0f, static_cast<float>(400) / 2.0f },
				1.0,
				Vertex3f{ .0f, 1.0f, 1.0f },
				400,
				400);

			for (uint i = 0; i < manager->getSize(); i++)
			{
				Assert::IsFalse(manager->getBomb(i)->isActive());
			}

			auto bomb = manager->getBomb(1);
			Assert::IsNotNull(bomb);

			bomb->setActive();

			for (uint i = 0; i < manager->getSize(); i++)
			{
				if (i == 1)
				{
					Assert::IsTrue(manager->getBomb(i)->isActive());
					break;
				}
				Assert::IsFalse(manager->getBomb(i)->isActive());
			}

			for (uint i = 0; i < manager->getSize(); i++)
			{
				manager->updateTime(.9f);
			}

			Assert::IsFalse(manager->getBomb(1)->isActive());
			///....
		}
		TEST_METHOD(TEST_METHOS3)
		{
			uint w = 800;
			uint h = 600;
			auto _s_ptr = std::make_shared<Square>(
				Vertex2f{ w / 2.0f, h / 2.0f },
				10.0f,
				Vertex3f{ .0f, 1.0f, .0f },
				w,
				h);

			Vertex2f _center = _s_ptr->getCenter();
			float _side_w = 10.0f / static_cast<float>(w) * 2.0f;
			float _side_h = 10.0f / static_cast<float>(h) * 2.0f;

			Assert::AreEqual(_side_w, _s_ptr->getSideW());
			Assert::AreEqual(_side_h, _s_ptr->getSideH());

			float _center_x = ((static_cast<float>(w) / 2.0f) / static_cast<float>(w)* 2.0f) - 1.0f + _side_w / 2.0f;
			float _center_y = ((static_cast<float>(h) / 2.0f) / static_cast<float>(h)* 2.0f) - 1.0f - _side_h / 2.0f;

			Assert::AreEqual(_center_x, _center.x);
			Assert::AreEqual(_center_y, _center.y);

			//map
//			auto _vec2d = Map::loadMapFromFile("mapa.txt");
		//	if (_vec2d == nullptr)
		//		Assert::Fail();

		}
    };
}