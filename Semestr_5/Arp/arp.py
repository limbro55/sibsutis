from flask import Flask, jsonify, request
import signal
import sys
import time

app = Flask(__name__)

# База данных в памяти
items = [
    {"id": 1, "name": "Banana", "quantity": 10, "category": "fruit"},
    {"id": 2, "name": "Apple", "quantity": 5, "category": "fruit"},
    {"id": 3, "name": "Carrot", "quantity": 8, "category": "vegetable"}
]

# Swagger
SWAGGER_URL = '/api/docs'
API_URL = '/static/swagger.json'

try:
    from flask_swagger_ui import get_swaggerui_blueprint
    swaggerui_blueprint = get_swaggerui_blueprint(
        SWAGGER_URL,
        API_URL,
        config={'app_name': "Items API"}
    )
    app.register_blueprint(swaggerui_blueprint, url_prefix=SWAGGER_URL)
except ImportError:
    print("Flask-Swagger-UI not installed, Swagger UI will not be available")

@app.route('/name', methods=['GET'])
def name_page():
    name = "Данил Сафонов"
    return jsonify(name)

@app.route('/api/items', methods=['GET'])
def get_items():
    return jsonify(items)

@app.route('/api/items/<int:item_id>', methods=['GET'])
def get_item(item_id):
    item = next((item for item in items if item['id'] == item_id), None)
    if item:
        return jsonify(item)
    return jsonify({"error": "Item not found"}), 404

@app.route('/api/items', methods=['POST'])
def create_item():
    data = request.get_json() or {}
    if 'name' not in data:
        return jsonify({"error": "Name is required"}), 400
    new_item = {
        "id": len(items) + 1,
        "name": data['name'],
        "quantity": data.get('quantity', 0),
        "category": data.get('category', 'other')
    }
    items.append(new_item)
    return jsonify(new_item), 201

@app.route('/api/items/<int:item_id>', methods=['PUT'])
def update_item(item_id):
    item = next((item for item in items if item['id'] == item_id), None)
    if not item:
        return jsonify({"error": "Item not found"}), 404
    data = request.get_json() or {}
    item['name'] = data.get('name', item['name'])
    item['quantity'] = data.get('quantity', item['quantity'])
    item['category'] = data.get('category', item['category'])
    return jsonify(item)

@app.route('/api/items/<int:item_id>', methods=['DELETE'])
def delete_item(item_id):
    global items
    items = [item for item in items if item['id'] != item_id]
    return jsonify({"message": "Item deleted"})

@app.route('/static/swagger.json')
def swagger_json():
    swagger_spec = {
        "openapi": "3.0.0",
        "info": {"title": "Items API", "version": "1.0.0"},
        "paths": {
            "/api/items": {
                "get": {"summary": "Get all items", "responses": {"200": {"description": "Success"}}},
                "post": {"summary": "Create item", "responses": {"201": {"description": "Created"}}}
            },
            "/api/items/{id}": {
                "get": {"summary": "Get item by ID", "responses": {"200": {"description": "Success"}}},
                "put": {"summary": "Update item", "responses": {"200": {"description": "Updated"}}},
                "delete": {"summary": "Delete item", "responses": {"200": {"description": "Deleted"}}}
            }
        }
    }
    return jsonify(swagger_spec)

def graceful_shutdown(signum, frame):
    print(f"\nПолучен сигнал {signum}. Graceful shutdown...")
    time.sleep(1)
    sys.exit(0)

signal.signal(signal.SIGTERM, graceful_shutdown)
signal.signal(signal.SIGINT, graceful_shutdown)

if __name__ == '__main__':
    print("Запуск приложения Flask API без HTML...")
    app.run(host='0.0.0.0', port=5000, debug=False)
else:
    # Для запуска через Gunicorn
    application = app