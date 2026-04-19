import * as THREE from 'three';

var scene;
var camera;
var renderer;


var init = function() {

    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );

    renderer = new THREE.WebGLRenderer();
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.body.appendChild( renderer.domElement );

    this.render();

};

var render = function() {
    requestAnimationFrame( render );
    renderer.render( scene, camera );
}

var createACube = function() {
    var geometry = new THREE.BoxGeometry( 1, 1, 1); 
    var material = new THREE.MeshBasicMaterial( {color: "red"});
    cube = new THREE.Mesh(geometry, material);
    scene.add( cube );
}

window.onload = this.init;